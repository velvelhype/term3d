#include "./include/term3d.h"
#include "./include/vector.h"

void	init_vars(t_vector eye_dir, t_moller *vars, t_vector *eye_pos, t_tri *t)
{
	vars->epsilon = 0.000000001;
	vars->e1 = sub(&t->v1, &t->v0);
	vars->e2 = sub(&t->v2, &t->v0);
	cross(&vars->alpha, &eye_dir, &vars->e2);
	vars->det = dot(&vars->e1, &vars->alpha);
	if (-vars->epsilon < vars->det && vars->det < vars->epsilon)
	{
		vars->det = 0;
		return ;
	}
	vars->invDet = 1.0f / vars->det;
	vars->r = sub(eye_pos, &t->v0);
	cross(&vars->beta, &vars->r, &vars->e1);
}

void	is_ray_in_tri(t_tri tri, t_vector eye_dir, t_term *term, t_albedo *alb)
{
	t_moller	vars;
	float		u;
	float		v;
	float		t;

	init_vars(eye_dir, &vars, &term->eye_pos, &tri);
	if (vars.det == 0)
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
	is_min_dis(tri, mult(&eye_dir, t), term, alb);
}

float	moller97(t_vector eye_dir, t_term *tm, t_ply *p)
{
	t_tri		tri;
	int			i;
	t_albedo	alb_info;

	i = 0;
	init_vector(&alb_info.min_dis, -1, -1, -1);
	while (i < p->elem_faces)
	{
		tri.v0 = mult(&p->vertexes[p->faces[i].v1], tm->zoom);
		tri.v1 = mult(&p->vertexes[p->faces[i].v2], tm->zoom);
		tri.v2 = mult(&p->vertexes[p->faces[i].v3], tm->zoom);
		is_ray_in_tri(tri, eye_dir, tm, &alb_info);
		i++;
	}
	if (alb_info.min_dis.x != -1)
		return (calc_albedo(eye_dir, alb_info));
	return (-1);
}

float	is_colided(int x, int y, t_term *term_info, t_ply *ply_info)
{
	t_vector	screen_pos;
	t_vector	eye_dir;

	init_vector(&screen_pos, x, y, term_info->screen_z);
	eye_dir = sub(&screen_pos, &(term_info->eye_pos));
	return (moller97(eye_dir, term_info, ply_info));
}
