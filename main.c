#include "./include/term3d.h"
#include "./include/parse_ply.h"

void	end(void)
{
	if (system("leaks -q term3d > /dev/null"))
		system("leaks -q term3d");
}

int	exit_w_msg(char *msg)
{
	printf(TERM3D);
	printf("%s", msg);
	exit(0); // check err code exit should return.
}

void	init_term(t_term *tm)
{
	tm->height = 0;
	tm->screen_z = SCREEN_Z;
	init_vector(&(tm->eye_pos), 0, 0, CAMERA_Z);
	tm->zoom = DEFAULT_ZOOM;
	tm->sin = sin(ROTATION);
	tm->cos = cos(ROTATION);
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
			exit_w_msg(ERR_TOO_SHORT);
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
	t_ply	ply;

	if (!(argc == 2 || argc == 3))
		exit_w_msg(ERR_ARG);
	validate_argfile(argv[1]);
	load_obj(&ply);
	init_term(&tm);
	set_pxlchar(argc, argv[2], &tm);
	loop_draw(&tm, &ply);
	return (0);
}
