#include "./include/term3d.h"
#include "./include/parse_ply.h"

void	end(void)
{
	if (system("leaks -q term3d > /dev/null"))
		system("leaks -q term3d");
}

int	exit_me(char *s)
{
	printf("%s", s);
	exit(0);
}

void	init_info(t_term *info)
{
	info->height = 0;
	info->screen_z = 0;
	init_vector(&(info->eye_pos), 0, 0, -100);
	init_vector(&(info->sphere_pos), 0, 0, 0);
	info->sphere_r = 10;
	info->zoom = 8;
	info->deg = 0.01;
	info->charset = NULL;
}

int	main(int argc, char **argv)
{
	t_term	tm;
	t_ply	*ply;

	if (!(argc == 2 || argc == 3))
		exit_me(ERR_ARG);
	ply = parse_ply(argv[1]);
	if (ply == NULL)
		exit_me(ERR_PARSE);
	init_info(&tm);
	if (argc == 3)
	{
		tm.charset = argv[2];
		tm.charset_size = strlen(argv[2]);
	}
	else
	{
		tm.charset = " -~=cxFX8NNNNN";
		tm.charset_size = 10;
	}
	tm.threshold = (int)(tm.charset_size * 0.4);
	loop_draw(&tm, ply);
	return (0);
}
