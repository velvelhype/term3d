#ifndef TERM3D_H
#define TERM3D_H

#include "vector.h"

typedef struct s_moller
{
	float	kEpsilon;
	t_vector	e1;
	t_vector	e2;
	t_vector	alpha;
	float	det;
	float	invDet;
	t_vector	r;
	t_vector	beta;
}	t_moller;

typedef struct s_tri
{
	t_vector v0;
	t_vector v1;
	t_vector v2;
}	t_tri;

typedef struct s_term
{
	int width;
	int height;
	int screen_z;
	int	zoom;
	float	deg;
	t_vector	eye_pos;
	t_vector	sphere_pos;
	int			sphere_r;
} t_term;

#define M_PI   3.14159265358979323846264338327950288
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

#include "./include/parse_ply.h"
float	is_colided(int x, int y, t_term *info, t_ply *ply_info);

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "./include/parse_ply.h"

#endif
