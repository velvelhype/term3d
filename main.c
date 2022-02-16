#include "term3d.h"
#include "./include/parse_ply.h"

// commented by tyamagis
// 2
void	init_info(t_term *info)
{
	info->height = 30;
	info->width = 30;
	info->screen_z = 0;
	init_vector(&(info->eye_pos), 0, 0, -10);
	init_vector(&(info->sphere_pos), 0, 0, 0);
	info->sphere_r = 10;
}

int main(int argc, char **argv)
{
	t_term	term_info;
	t_ply	*ply_info;
	char	*filename;

	if(argc != 2)
		return 0;
	filename = argv[argc - 1];
	ply_info = parse_ply(filename);
	init_info(&term_info);
	int x = -1 * (term_info.width) / 2;
	int y = 1 * (term_info.height) / 2;
	while(y > -1 * term_info.width / 2)
	{
		while(x < term_info.height / 2)
		{
			// （x, y）が円と衝突しているか判定
			float D = is_colided(x, y, &term_info, ply_info);
			if (D >= 0)
				printf("▩");
			else
				printf(".");
			printf(" ");
			x++;
		}
		printf("\n");
		x = -1 * (term_info.width) / 2;
		y--;
	}
}
