#include "./include/vector.h"

t_vector	add(const t_vector *a, const t_vector *b)
{
	t_vector	ret;

	ret.x = a->x + b->x;
	ret.y = a->y + b->y;
	ret.z = a->z + b->z;
	return (ret);
}

t_vector	sub(const t_vector *a, const t_vector *b)
{
	t_vector	ret;

	ret.x = a->x - b->x;
	ret.y = a->y - b->y;
	ret.z = a->z - b->z;
	return (ret);
}

t_vector	mult(const t_vector *a, float b)
{
	t_vector	ret;

	ret.x = a->x * b;
	ret.y = a->y * b;
	ret.z = a->z * b;
	return (ret);
}

float	dot(const t_vector *a, const t_vector *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

void	cross(t_vector *o, const t_vector *a, const t_vector *b)
{
	o->x = a->y * b->z - a->z * b->y;
	o->y = a->z * b->x - a->x * b->z;
	o->z = a->x * b->y - a->y * b->x;
}
