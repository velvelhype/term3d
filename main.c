#include "term3d.h"

// commented by tyamagis
// 2
void	init_info(t_term *info)
{
	info->height = 30;
	info->width = 30;
	t_vector eye = {0, 0, 0};
}

int main()
{
	t_term info;

	init_info(&info);
	int x = 0;
	int y = 0;
	while(y < info.height)
	{
		while(x < info.width)
		{
			// （x, y）が図形と衝突しているか判定
			// is_colided(x, y);
			printf("▩");
			//
			printf(" ");
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
}
