#include "./include/term3d.h"
#include "./include/parse_ply.h"

void end(void)
{
        if (system("leaks -q term3d > /dev/null"))
        system("leaks -q term3d");
}

int	exit_me(void)
{
	printf("term3d >> something wrong. retry.\n");
	exit(0);
}

void	init_info(t_term *info)
{
	struct winsize	w;
	int				size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	size = w.ws_col * 0.5;
	if (size > w.ws_row)
		size = w.ws_row;
	info->height = size;
	info->width = size;
	info->lim_x = size * 0.5;
	info->lim_y = size * -0.5;
	info->screen_z = 0;
	init_vector(&(info->eye_pos), 0, 0, -100);
	init_vector(&(info->sphere_pos), 0, 0, 0);
	info->sphere_r = 10;
	info->zoom = 8;
	info->deg = 0.01;
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
