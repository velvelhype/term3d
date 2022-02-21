#include "./include/term3d.h"
#include "./include/vector.h"

t_vector	calc_normal_vector(t_tri tri)
{
	t_vector	ab;
	t_vector	ac;
	t_vector	normal_vector;

	ab = sub(&tri.v1, &tri.v0);
	ac = sub(&tri.v2, &tri.v0);
	cross(&normal_vector, &ab, &ac);
	normalize(&normal_vector);
	return (normal_vector);
}

float	calc_albedo(t_vector eye_dir, t_albedo alb_info)
{
	float		conc;

	mult(&eye_dir, -1);
	normalize(&eye_dir);
	conc = dot(&alb_info.face_normal_vec, &eye_dir);
	conc *= -1;
	return (conc);
}

void	is_min_dis(t_tri tri, t_vector e, t_term *term, t_albedo *alb)
{
	t_vector	distance;

	distance = e;
	distance = add(&term->eye_pos, &distance);
	if (alb->min_dis.x == -1)
	{
		alb->face_normal_vec = calc_normal_vector(tri);
		alb->min_dis = distance;
		return ;
	}
	if (len_vector(&distance, &term->eye_pos)
		< len_vector(&alb->min_dis, &term->eye_pos))
	{
		alb->face_normal_vec = calc_normal_vector(tri);
		alb->min_dis = distance;
	}
}
