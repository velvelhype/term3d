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

typedef struct s_tri
{
	t_vector v0;
	t_vector v1;
	t_vector v2;
}	t_tri;

float	judge(t_tri tri, t_vector eye_dir, t_term *info)
{
    float kEpsilon = 1e-6f;
	t_vector e1 = sub(&tri.v1, &tri.v0);
	t_vector e2 = sub(&tri.v2, &tri.v0);
	t_vector alpha;
	cross(&alpha, &eye_dir, &e2);
	float det = dot(&e1, &alpha);
	if (-kEpsilon < det && det < kEpsilon)
		return -1;
	float invDet = 1.0f / det;
	t_vector r = sub(&info->eye_pos, &tri.v0);

	float u = dot(&alpha, &r) * invDet;
	if (u < 0.0f || u > 1.0f)
		return -1;
	
	t_vector beta;
	cross(&beta, &r, &e1);
	float v = dot(&eye_dir, &beta) * invDet;
	if ( v < 0.0f || u + v > 1.0f)
		return -1;

	float t = dot(&e2,& beta) * invDet;
	if (t < 0.0f)
		return -1;
	return 0;
}

float	moller97(t_vector eye_dir, t_term *info)
{
    // constexpr float kEpsilon = 1e-6f;
	int max = 4;
	t_tri	tri[max];
	init_vector(&tri[0].v0, 5, 10, 0);
	init_vector(&tri[0].v1, 0, -10, 0);
	init_vector(&tri[0].v2, 10, 0, 0);

	init_vector(&tri[1].v0, -10, 10, 0);
	init_vector(&tri[1].v1, 0, -10, 0);
	init_vector(&tri[1].v2, -10, 0, 0);

	init_vector(&tri[2].v0, 30, -10, 0);
	init_vector(&tri[2].v1, 0, -10, 0);
	init_vector(&tri[2].v2, -10, -20, 0);

	int i = 0;
	while (i < max)
	{
		if (judge(tri[i], eye_dir, info) == 0)
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
	//二次方程式　今は円と衝突判定してる
	// return (quadratic_equation(eye_dir, obj_to_eye, info));
	//三角形との衝突計算

	return (moller97(eye_dir, info));
}