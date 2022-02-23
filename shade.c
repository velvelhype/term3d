#include "./include/term3d.h"
#include "./include/vector.h"

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

float	calc_reflectance(t_vector eye_dir, t_forefront alb_info)
{
	float		reflectance;

	mult_vecs(&eye_dir, -1);
	normalize(&eye_dir);
	reflectance = dot_vecs(&alb_info.face_normal_vec, &eye_dir);
	reflectance *= -1;
	return (reflectance);
}

void	try_update_forefront(t_tri tri, t_vector eye_dir, \
	t_term *term, t_forefront *forefront_face)
{
	t_vector	distance;

	distance = eye_dir;
	distance = add_vecs(&term->eye_pos, &distance);
	if (forefront_face->is_exist == FALSE)
	{
		forefront_face->is_exist = TRUE;
		forefront_face->face_normal_vec = calc_normal_vector(tri);
		forefront_face->min_dis = distance;
		return ;
	}
	if (len_vector(&distance, &term->eye_pos)
		< len_vector(&forefront_face->min_dis, &term->eye_pos))
	{
		forefront_face->face_normal_vec = calc_normal_vector(tri);
		forefront_face->min_dis = distance;
	}
}
