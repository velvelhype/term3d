#include "./include/term3d.h"
#include "./include/parse_ply.h"

void	end(void)
{
	if (system("leaks -q term3d > /dev/null"))
		system("leaks -q term3d");
}

int	exit_with_msg(char *msg)
{
	printf(TERM3D);
	printf("%s", msg);
	exit(0);
}

void	init_term(t_term *tm)
{
	tm->size = 0;
	tm->screen_z = SCREEN_Z;
	init_vector(&(tm->eye_pos), 0, 0, CAMERA_Z);
	tm->rotate_sin = sin(ROTATION);
	tm->rotate_cos = cos(ROTATION);
	tm->charset = NULL;
}

void	set_pxlchar(int ac, char *arg_chars, t_term *tm)
{
	size_t	charset_size;

	if (ac == 3)
	{
		charset_size = strlen(arg_chars);
		if (charset_size > MIN_CHARS)
		{
			tm->charset = arg_chars;
			tm->charset_size = charset_size;
		}
		else
			exit_with_msg(ERR_TOO_SHORT);
	}
	else
	{
		tm->charset = DEF_CHARSET;
		tm->charset_size = SIZE_CHARSET;
	}
	tm->threshold = (int)(tm->charset_size * THRESHOLD);
	return ;
}

int	main(int argc, char **argv)
{
	t_term	tm;
	t_ply	*ply;

	if (!(argc == 2 || argc == 3))
		exit_with_msg(ERR_ARG);
	ply = parse_ply(argv[1]);
	init_term(&tm);
	set_pxlchar(argc, argv[2], &tm);
	loop_draw(&tm, ply);
	return (0);
}
