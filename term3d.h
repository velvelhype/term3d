#ifndef TERM3D_H
#define TERM3D_H

typedef struct s_vector
{
	float x;
	float y;
	float z;
} t_vector;

typedef struct s_term
{
	int width;
	int height;
	t_vector eye_pos;
} t_term;

#include <stdio.h>
#include <string.h>

#endif
