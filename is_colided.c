#include "term3d.h"
#include "vector_utils.h"

float quadratic_equation(t_vector eye_dir, t_vector obj_to_eye, t_term *info)
{
    float A, B, C, D;

    A = squared_norm(&eye_dir);
    B = 2 * dot(&eye_dir, &obj_to_eye);
    C = squared_norm(&obj_to_eye) - SQR(info->sphere_r);
    D = SQR(B) - 4 * A * C;	
	return (D);
}

float	is_colided(int x, int y, t_term *info)
{
	// calculate eyedir
	t_vector screen_pos  = {x, y, info->screen_z};
	t_vector eye_dir = sub(&screen_pos, &(info->eye_pos));
	t_vector obj_to_eye = sub(&(info->eye_pos), &(info->sphere_pos));
	//二次方程式
	return (quadratic_equation(eye_dir, obj_to_eye, info));
	// printf("%s\n", vector_str(&screen_pos));
	exit(1);
	// eyedirと物体が交差しているか判定して出力
}