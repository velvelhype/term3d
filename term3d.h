#ifndef TERM3D_H
#define TERM3D_H

#include "vector_utils.h"

typedef struct s_term
{
	int width;
	int height;
	int screen_z;
	t_vector	eye_pos;
	t_vector	sphere_pos;
	int			sphere_r;
} t_term;

float	is_colided(int x, int y, t_term *info);

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#endif
