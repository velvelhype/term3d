#include "./include/term3d.h"
#include "./include/vector.h"

void	init_vars(t_vector eye_dir, t_moller *vars, t_vector *eye_pos, t_tri *t)
{
	vars->e1 = sub_vecs(&t->v1, &t->v0);
	vars->e2 = sub_vecs(&t->v2, &t->v0);
	cross_vecs(&vars->alpha, &eye_dir, &vars->e2);
	vars->det = dot_vecs(&vars->e1, &vars->alpha);
	if (EPSILON < vars->det && vars->det < EPSILON)
	{
		vars->det = 0;
		return ;
	}
	vars->invDet = 1.0f / vars->det;
	vars->r = sub_vecs(eye_pos, &t->v0);
	cross_vecs(&vars->beta, &vars->r, &vars->e1);
}

float	simul_equations(t_tri tri, t_vector eye_dir, t_term *term)
{
	t_moller	vars;
	float		u;
	float		v;
	float		t;

	init_vars(eye_dir, &vars, &term->eye_pos, &tri);
	if (vars.det == 0)
		return (-1);
	u = dot_vecs(&vars.alpha, &vars.r) * vars.invDet;
	if (u < 0.0f || u > 1.0f)
		return (-1);
	v = dot_vecs(&eye_dir, &vars.beta) * vars.invDet;
	if (v < 0.0f || u + v > 1.0f)
		return (-1);
	t = dot_vecs(&vars.e2, &vars.beta) * vars.invDet;
	if (t < 0.0f)
		return (-1);
	return (t);
}

float	crossing_detection(t_vector eye_dir, t_term *tm,
	t_ply *p, t_forefront	*forefront)
{
	t_tri		tri;
	int			i;
	float		equations_return;

	forefront->is_exist = FALSE;
	i = 0;
	while (i < p->elem_faces)
	{
		tri.v0 = p->vertexes[p->faces[i].v1];
		tri.v1 = p->vertexes[p->faces[i].v2];
		tri.v2 = p->vertexes[p->faces[i].v3];
		equations_return = simul_equations(tri, eye_dir, tm);
		if (equations_return != -1)
			try_update_forefront(tri, mult_vecs(&eye_dir, equations_return), \
					forefront);
		i++;
	}
	return (-1);
}

float	calc_crossing_eye_dir_and_face(int x, int y, \
	t_term *term_info, t_ply *ply_info)
{
	t_forefront	forefront;
	t_vector	screen_pos;
	t_vector	eye_dir;

	init_vector(&screen_pos, x, y, term_info->screen_z);
	eye_dir = sub_vecs(&screen_pos, &(term_info->eye_pos));
	crossing_detection(eye_dir, term_info, ply_info, &forefront);
	if (forefront.is_exist == TRUE)
		return (calc_reflectance(eye_dir, forefront));
	return (-1);
}
