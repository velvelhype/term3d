#include "./include/term3d.h"
#include "./include/vector.h"

void	init_vars(t_vector eye_dir, t_moller *vars, t_vector *eye_pos, t_tri *t)
{
	vars->kEpsilon = 0.000000001;
	vars->e1 = sub(&t->v1, &t->v0);
	vars->e2 = sub(&t->v2, &t->v0);
	cross(&vars->alpha, &eye_dir, &vars->e2);
	vars->det = dot(&vars->e1, &vars->alpha);
	vars->invDet = 1.0f / vars->det;
	vars->r = sub(eye_pos, &t->v0);
	cross(&vars->beta, &vars->r, &vars->e1);
}

t_vector	calc_normal_vector(t_tri tri)
{
	t_vector ab = sub(&tri.v1, &tri.v0);
	t_vector ac = sub(&tri.v2, &tri.v0);
	t_vector normal_vector;

	cross(&normal_vector, &ab, &ac);
	normalize(&normal_vector);
	return	(normal_vector);
}

void	is_ray_in_tri(t_tri tri, t_vector eye_dir, t_term *term_info, t_albedo *alb_info)
{
	t_moller	vars;
	float		u; 
	float		v;
	float		t;

	init_vars(eye_dir, &vars, &term_info->eye_pos, &tri);
	if (-vars.kEpsilon < vars.det && vars.det < vars.kEpsilon)
		return ;
	u = dot(&vars.alpha, &vars.r) * vars.invDet;
	if (u < 0.0f || u > 1.0f)
		return ;
	v = dot(&eye_dir, &vars.beta) * vars.invDet;
	if (v < 0.0f || u + v > 1.0f)
		return ;
	t = dot(&vars.e2, &vars.beta) * vars.invDet;
	if (t < 0.0f)
		return ;

//////////////////////////////////////////////////////////
	t_vector	distance =  mult(&eye_dir, t);
	distance = add(&term_info->eye_pos, &distance);
	if (alb_info->min_dis.x == -1)
	{
		alb_info->face_normal_vec = calc_normal_vector(tri);
		alb_info->min_dis = distance;
		return ;
	}
	if (len_vector(&distance, &term_info->eye_pos)
	< len_vector(&alb_info->min_dis, &term_info->eye_pos))
	{
		alb_info->face_normal_vec = calc_normal_vector(tri);
		alb_info->min_dis = distance;
		return ;
	}
	else
		return ;
}

void	vertex_conversion(t_vector *ver, t_term *i)
{
	float	new_x;
	float	new_y;

	new_x = ver->x * cos(i->deg) - ver->y * sin(i->deg);
	new_y = ver->x * sin(i->deg) + ver->y * cos(i->deg);
	ver->x = new_x;
	ver->y = new_y;
	*ver = mult(ver, i->zoom);
}

#define MIN(a,b) (a < b ? a : b)
#define MAX(a,b) (a > b ? a : b)
#define CLAMP(v,minv,maxv) MIN(MAX(v,minv),maxv)

float	moller97(t_vector eye_dir, t_term *term_info, t_ply *ply_info)
{
	t_tri	tri;
	int		i;

	i = 0;
	t_albedo	alb_info;
	init_vector(&alb_info.min_dis, -1, -1, -1);

	while (i < ply_info->elem_faces)
	{
		tri.v0 = ply_info->vertexes[ply_info->faces[i].v1];
		vertex_conversion(&tri.v0, term_info);
		tri.v1 = ply_info->vertexes[ply_info->faces[i].v2];
		vertex_conversion(&tri.v1, term_info);
		tri.v2 = ply_info->vertexes[ply_info->faces[i].v3];
		vertex_conversion(&tri.v2, term_info);
		is_ray_in_tri(tri, eye_dir, term_info, &alb_info);
		i++;
	}
	if (alb_info.min_dis.x != -1)
	{
		mult(&eye_dir, -1);
		normalize(&eye_dir);
		float conc = dot(&alb_info.face_normal_vec, &eye_dir);
		conc *= -1;
		return (conc);
	}
	return (-1);
}

float	is_colided(int x, int y, t_term *term_info, t_ply *ply_info)
{
	t_vector	screen_pos;
	t_vector	eye_dir;
	t_vector	obj_to_eye;

	init_vector(&screen_pos, x, y, term_info->screen_z);
	eye_dir = sub(&screen_pos, &(term_info->eye_pos));
	obj_to_eye = sub(&(term_info->eye_pos), &(term_info->sphere_pos));
	return (moller97(eye_dir, term_info, ply_info));
}
