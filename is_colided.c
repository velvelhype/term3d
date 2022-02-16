#include "term3d.h"
#include "vector.h"

float	quadratic_equation(t_vector eye_dir, t_vector obj_to_eye, t_term *info)
{
    float A, B, C, D;
    A = squared_norm(&eye_dir);
    B = 2 * dot(&eye_dir, &obj_to_eye);
    C = squared_norm(&obj_to_eye) - SQR(info->sphere_r);
    D = SQR(B) - 4 * A * C;	

	return (D);
}

void	init_t_moller(t_vector eye_dir, t_moller *vars, t_term *info, t_tri *tri)
{
    vars->kEpsilon = 1e-6f;
	vars->e1 = sub(&tri->v1, &tri->v0);
	vars->e2 = sub(&tri->v2, &tri->v0);
	cross(&vars->alpha, &eye_dir, &vars->e2);
	vars->det = dot(&vars->e1, &vars->alpha);
	vars->invDet = 1.0f / vars->det;
	vars->r = sub(&info->eye_pos, &tri->v0);
	cross(&vars->beta, &vars->r, &vars->e1);
}


float	is_ray_in_tri(t_tri tri, t_vector eye_dir, t_term *info)
{
	t_moller vars;
	init_t_moller(eye_dir, &vars, info, &tri);

	if (-vars.kEpsilon < vars.det && vars.det < vars.kEpsilon)
		return -1;
	float u = dot(&vars.alpha, &vars.r) * vars.invDet;
	if (u < 0.0f || u > 1.0f)
		return -1;
	float v = dot(&eye_dir, &vars.beta) * vars.invDet;
	if ( v < 0.0f || u + v > 1.0f)
		return -1;
	float t = dot(&vars.e2, &vars.beta) * vars.invDet;
	if (t < 0.0f)
		return -1;

	return 0;
}

float	moller97(t_vector eye_dir, t_term *info)
{
	int		max = 2;
	t_tri	tri[max];

	init_vector(&tri[0].v0, 0, 0, 0);
	init_vector(&tri[0].v1, 10, 0, 0);
	init_vector(&tri[0].v2, 0, 10, 0);
	init_vector(&tri[1].v0, 0, 0, 0);
	init_vector(&tri[1].v1, 0, -10, 0);
	init_vector(&tri[1].v2, -10, 0, 0);
	// init_vector(&tri[2].v0, 30, -10, 0);
	// init_vector(&tri[2].v1, 0, -10, 0);
	// init_vector(&tri[2].v2, -10, -20, 0);
	int i = 0;
	while (i < max)
	{
		if (is_ray_in_tri(tri[i], eye_dir, info) == 0)
			return (1);
		i++;
	}

	return (-1);
}

float	is_colided(int x, int y, t_term *info)
{
	// calculate eyedir
	t_vector screen_pos  = {x, y, info->screen_z};
	t_vector eye_dir = sub(&screen_pos, &(info->eye_pos));
	t_vector obj_to_eye = sub(&(info->eye_pos), &(info->sphere_pos));
	// 二次方程式　今は円と衝突判定してる
	// return (quadratic_equation(eye_dir, obj_to_eye, info));
	// 三角形との衝突計算
	return (moller97(eye_dir, info));
}