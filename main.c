#include "term3d.h"

void	init_info(t_term *info)
{
	info->height = 30;
	info->width = 30;
	info->screen_z = -5;
	info->eye_pos.x = 0;
	info->eye_pos.y = 0;
	info->eye_pos.z = -10;
	info->sphere_pos.x = 0;
	info->sphere_pos.y = 0;
	info->sphere_pos.z = 0;
	info->sphere_r = 9;
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
			// （x, y）が図形と衝突しているか判定
			if (is_colided(x, y, &info) >= 0)
				printf("▩");
			else
				printf(" ");
			printf(" ");
			x++;
		}
		printf("\n");
		x = -1 * (info.width) / 2;
		y++;
	}
}