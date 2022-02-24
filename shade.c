#include "./include/term3d.h"
#include "./include/vector.h"
#include "./include/simple_operation.h"

t_vector	calc_normal_vector(t_tri tri)
{
	t_vector	ab;
	t_vector	ac;
	t_vector	normal_vector;

	ab = sub_vecs(&tri.v1, &tri.v0);
	ac = sub_vecs(&tri.v2, &tri.v0);
	cross_vecs(&normal_vector, &ab, &ac);
	normalize(&normal_vector);
	return (normal_vector);
}

void	try_update_forefront(t_tri tri, t_vector eye_dir, \
	t_forefront *forefront)
{
	float	distance;
	distance = norm(&eye_dir);
	if (forefront->is_exist == FALSE)
	{
		forefront->is_exist = TRUE;
		forefront->face_normal_vec = calc_normal_vector(tri);
		forefront->min_dis = distance;
		return ;
	}
	if (distance < forefront->min_dis)
	{
		forefront->face_normal_vec = calc_normal_vector(tri);
		forefront->min_dis = distance;
	}
}

float	calc_reflectance(t_vector eye_dir, t_forefront alb_info)
{
	float		reflectance;

	mult_vecs(&eye_dir, -1);
	normalize(&eye_dir);
	reflectance = dot_vecs(&alb_info.face_normal_vec, &eye_dir);
	reflectance = mod(reflectance);
	return (reflectance);
}
