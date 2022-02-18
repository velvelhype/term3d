#include "term3d.h"
#include "./include/parse_ply.h"

// commented by tyamagis
void	init_info(t_term *info)
{
	info->height = 60;
	info->width = 60;
	info->screen_z = 0;
	init_vector(&(info->eye_pos), 0, 0, -10);
	init_vector(&(info->sphere_pos), 0, 0, 0);
	info->sphere_r = 10;
	info->zoom= 8;
	info->deg = 0;
}

int main(int argc, char **argv)
{
	t_term	term_info;
	t_ply	*ply_info;
	char	*filename;
	char	*output_data;
	char	*tmp;
	size_t	datasize;
	int		frame;

	if(argc != 2)
		return 0;
	filename = argv[argc - 1];
	ply_info = parse_ply(filename);
	init_info(&term_info);

	int x = -1 * (term_info.width) / 2;
	int y = 1 * (term_info.height) / 2;
	datasize = (term_info.width + 1) * (term_info.height + 1) + 1;
	output_data = (char *)malloc(datasize);
	tmp = output_data;
	frame = 0;
	while(1)
	{
		printf("%d\n", frame++);
		output_data = tmp;
		fprintf(stdout, "\033[2J\033[2H");
		while(y > -1 * term_info.width / 2)
		{
			while(x < term_info.height / 2)
			{
				// （x, y）が円と衝突しているか判定
				float D = is_colided(x, y, &term_info, ply_info);
				if (D >= 0)
					memset(output_data, '#', 1);
				else
					memset(output_data, ' ', 1);
				output_data++;
				memset(output_data, ' ', 1);
				output_data++;
				x++;
			}
			memset(output_data, '\n', 1);
			output_data++;
			x = -1 * (term_info.width) / 2;
			y--;
		}
		memset(output_data, '\0', 1);
		printf("%s", tmp);
		term_info.deg += 10;
		y = 1 * (term_info.height) / 2;
		usleep(50000);
	}
}
