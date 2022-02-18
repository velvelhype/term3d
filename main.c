#include "term3d.h"
#include "./include/parse_ply.h"

int	exit_me(void)
{
	printf("term3d >> something wrong. retry.\n");
	exit(0);
}

void	init_info(t_term *info)
{
	info->height = 60; // GET terminal size
	info->width = 60; // GET terminal size
	info->lim_x = info->height * 0.5;
	info->lim_y = info->width * -0.5;
	info->screen_z = 0;
	init_vector(&(info->eye_pos), 0, 0, -50);
	init_vector(&(info->sphere_pos), 0, 0, 0);
	info->sphere_r = 10;
	info->zoom = 8;
	info->deg = 0;
	return ;
}

int	main(int argc, char **argv)
{
	t_term	tm;
	t_ply	*ply;

	if (argc != 2)
		exit_me();
	ply = parse_ply(argv[1]);
	if (ply == NULL)
		exit_me();
	init_info(&tm);
	loop_draw(&tm, ply);
	return (0);
}
