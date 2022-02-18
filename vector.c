#include "./include/vector.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

void	init_vector(t_vector *vec, float arg_x, float arg_y, float arg_z)
{
	vec->x = arg_x;
	vec->y = arg_y;
	vec->z = arg_z;
}

float	squared_norm(const t_vector*v)
{
	return (sqrt(v->x) + sqrt(v->y) + sqrt(v->z));
}

float	norm(const t_vector *v)
{
	return (sqrt(squared_norm(v)));
}

float	normalize(t_vector *v)
{
	float	vnorm;

	vnorm = norm(v);
	v->x /= vnorm;
	v->y /= vnorm;
	v->z /= vnorm;
	return (vnorm);
}
