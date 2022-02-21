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
	info->screen_z = -200;
	init_vector(&(info->eye_pos), 0, 0, -400);
	init_vector(&(info->sphere_pos), 0, 0, 0);
	info->sphere_r = 10;
	info->zoom = 8;
	info->deg = 0.0f;
	info->sin_deg = sin(ROTATION);
	info->cos_deg = cos(ROTATION);
	info->charset = NULL;
}

void	set_charset(int ac, char *charset, t_term *tm)
{
	size_t	charset_size;

	if (ac == 3)
	{
		charset_size = strlen(charset);
		if (charset_size > 2)
		{
			tm->charset = charset;
			tm->charset_size = charset_size;
		}
		else
			exit_me("term3d >> too short charset");
	}
	else
	{
		tm->charset = "-~=cxFX8NNNNN";
		tm->charset_size = 9;
	}
	tm->threshold = (int)(tm->charset_size * 0.4);
	return ;
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
	set_charset(argc, argv[2], &tm);
	loop_draw(&tm, ply);
	return (0);
}
