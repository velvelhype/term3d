#ifndef TERM3D_H
# define TERM3D_H

# define TRUE 1
# define FALSE 0
# define M_PI   3.14159265358979323846264338327950288
# define EPSILON 0.000000001

# define ROTATION 0.05f
# define SCREEN_Z -50
# define CAMERA_Z -150
# define DEF_ZOOM 8
# define MIN_CHARS 2
# define DEF_CHARSET "-~=cxFX8NNNNN"
# define SIZE_CHARSET 9
# define THRESHOLD 0.4

# define TERM3D "term3d >> "
# define ERR_ARG "invalid argument\n"
# define ERR_MALLOC "malloc failed\n"
# define NO_DISPLAY "nothing to display. quit.\n"
# define ERR_F_READ "error during file reading\n"
# define ERR_FMT "file format err. quit.\n"
# define ERR_PARSE "something wrong during file parse\n"
# define ERR_TOO_SHORT "too short charset\n"

# include "vector.h"
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <sys/ioctl.h>
# include "parse_ply.h"

typedef struct s_moller
{
	t_vector	e1;
	t_vector	e2;
	t_vector	alpha;
	float		det;
	float		invDet;
	t_vector	r;
	t_vector	beta;
}	t_moller;

typedef struct s_tri
{
	t_vector	v0;
	t_vector	v1;
	t_vector	v2;
}	t_tri;

typedef struct s_term
{
	int			width;
	int			height;
	int			lim_x;
	int			lim_y;
	int			screen_z;
	int			zoom;
	float		deg;
	double		cos;
	double		sin;
	t_vector	eye_pos;
	t_vector	sphere_pos;
	int			sphere_r;
	char		*charset;
	size_t		charset_size;
	int			threshold;
}	t_term;

typedef struct s_forefront
{
	int			is_exist;
	float		min_dis;
	t_vector	face_normal_vec;
}	t_forefront;

float		calc_crossing_eye_dir_and_face(int x, int y, t_term *i, t_ply *p);
t_vector	calc_normal_vector(t_tri tri);
float		calc_reflectance(t_vector eye_dir, t_forefront alb_info);
void		try_update_forefront(t_tri t, t_vector e, t_forefront *front);
void		loop_draw(t_term *tm, t_ply *ply);
int			exit_me(char *s);

#endif
