#include "term3d.h"
#include "./include/parse_ply.h"

int	exit_me(void)
{
	printf("term3d >> something wrong. retry.\n");
	exit(0);
}

void	init_info(t_term *info)
{
	info->height = 60;
	info->width = 60;
	info->screen_z = 0;
	init_vector(&(info->eye_pos), 0, 0, -50);
	init_vector(&(info->sphere_pos), 0, 0, 0);
	info->sphere_r = 10;
	info->zoom = 8;
	info->deg = 0;
}

void	set_char(int *xy, char *data, t_term *tm, t_ply *ply)
{
	float	d;

	while (xy[1] > -1 * tm.width / 2)
	{
		while (xy[0] < tm.height / 2)
		{
			d = is_colided(xy[0], xy[1], tm, ply);
			if (d >= 0)
			{
				memset(data, '+', 1);
				memset(data + 1, ' ', 1);
			}
			else
				memset(data, ' ', 2);
			data += 2;
			xy[0]++;
		}
		memset(data, '\n', 1);
		data++;
		xy[0] = -1 * (tm.width) / 2;
		xy[1]--;
	}
	memset(data, '\0', 1);
}

int	main(int argc, char **argv)
{
	t_term	tm;
	t_ply	*ply;
	char	*data;
	size_t	datasize;
	int		xy[2];

	if (argc != 2)
		exit_me();
	ply = parse_ply(argv[1]);
	init_info(&tm);
	xy[0] = -1 * (tm.width) / 2;
	xy[1] = 1 * (tm.height) / 2;
	datasize = (tm.width + 1) * (tm.height + 1) + 1;
	data = (char *)malloc(datasize);
	while (1)
	{
		fprintf(stdout, "\033[2J\033[2H");
		set_char(xy, data, &tm, ply);
		printf("%s", data);
		if (tm.deg > 360)
			tm.deg -= 360;
		tm.deg += 10;
		xy[1] = 1 * (tm.height) / 2;
		usleep(50000);
	}
}
