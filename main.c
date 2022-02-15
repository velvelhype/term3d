#include "term3d.h"

// commented by tyamagis
// 2
void	init_info(t_term *info)
{
	info->height = 30;
	info->width = 30;
	info->screen_z = -10;
	init_vector(&(info->eye_pos), 0, 0, -20);
	init_vector(&(info->sphere_pos), 0, 0, 0);
	info->sphere_r = 10;
}

int main()
{
	t_term info;

	init_info(&info);
	int x = -1 * (info.width) / 2;
	int y = -1 * (info.height) / 2;
	while(y < info.width / 2)
	{
		while(x < info.height / 2)
		{
			// （x, y）が円と衝突しているか判定
			float D = is_colided(x, y, &info);
			if (D >= 0)
				printf("▩");
			else
				printf(".");
			printf(" ");
			x++;
		}
		printf("\n");
		x = -1 * (info.width) / 2;
		y++;
	}
}
