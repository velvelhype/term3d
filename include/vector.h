#ifndef VECTOR_H
# define VECTOR_H

# include "macro.h"

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

void		init_vector(t_vector *vec, float arg_x, float arg_y, float arg_z);
t_vector	add(const t_vector *a, const t_vector *b);
t_vector	sub(const t_vector *a, const t_vector *b);
t_vector	mult(const t_vector *a, float b);
float		dot(const t_vector *a, const t_vector *b);
void		cross(t_vector *o, const t_vector *a, const t_vector *b);
float		squared_norm(const t_vector *v);
float		norm(const t_vector *v);
float		normalize(t_vector *v);

#endif
