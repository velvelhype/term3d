#include "term3d.h"
#include "vector.h"

float	quadratic_equation(t_vector eye_dir, t_vector obj_to_eye, t_term *term_info)
{
    float A, B, C, D;
    A = squared_norm(&eye_dir);
    B = 2 * dot(&eye_dir, &obj_to_eye);
    C = squared_norm(&obj_to_eye) - SQR(term_info->sphere_r);
    D = SQR(B) - 4 * A * C;	

	return (D);
}

void	init_t_moller(t_vector eye_dir, t_moller *vars, t_term *term_info, t_tri *tri)
{
    vars->kEpsilon = 1e-6f;
	vars->e1 = sub(&tri->v1, &tri->v0);
	vars->e2 = sub(&tri->v2, &tri->v0);
	cross(&vars->alpha, &eye_dir, &vars->e2);
	vars->det = dot(&vars->e1, &vars->alpha);
	vars->invDet = 1.0f / vars->det;
	vars->r = sub(&term_info->eye_pos, &tri->v0);
	cross(&vars->beta, &vars->r, &vars->e1);
}


float	is_ray_in_tri(t_tri tri, t_vector eye_dir, t_term *term_info)
{
	t_moller vars;
	init_t_moller(eye_dir, &vars, term_info, &tri);

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

float	moller97(t_vector eye_dir, t_term *term_info, t_ply *ply_info)
{
	t_tri	tri;

	int i = 0;
	while (i < ply_info->elem_faces)
	{
		tri.v0 = ply_info->vertexes[ply_info->faces[i].v1];
		tri.v0 = mult(&tri.v0, 7);
		tri.v1 = ply_info->vertexes[ply_info->faces[i].v2];
		tri.v1 = mult(&tri.v1, 7);
		tri.v2 = ply_info->vertexes[ply_info->faces[i].v3];
		tri.v2 = mult(&tri.v2, 7);
 		mult(&tri.v2, 10);
		if (is_ray_in_tri(tri, eye_dir, term_info) == 0)
			return (1);
		i++;
	}

	return (-1);
}

float	is_colided(int x, int y, t_term *term_info, t_ply *ply_info)
{

	// int i = 0;
	// while (i < ply_info->elem_vertexes)
	// {
	// 	printf("(%f, %f, %f)\n", ply_info->vertexes[i].x, ply_info->vertexes[i].y, ply_info->vertexes[i].z);
	// 	i++;
	// }
	
	// printf("\nface list : \n");
	// i = 0;
	// while (i < ply_info->elem_faces)
	// {
	// 	printf("%d idx : %d %d %d\n", i, ply_info->faces[i].v1, ply_info->faces[i].v2, ply_info->faces[i].v3);
	// 	i++;
	// }
	// return 0;

	// calculate eyedir
	t_vector screen_pos  = {x, y, term_info->screen_z};
	t_vector eye_dir = sub(&screen_pos, &(term_info->eye_pos));
	t_vector obj_to_eye = sub(&(term_info->eye_pos), &(term_info->sphere_pos));
	// 二次方程式　今は円と衝突判定してる
	// return (quadratic_equation(eye_dir, obj_to_eye, term_info));
	// 三角ポリゴンとの衝突計算
	return (moller97(eye_dir, term_info, ply_info));
}