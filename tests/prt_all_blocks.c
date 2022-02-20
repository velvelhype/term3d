#include <stdio.h>

int main(void)
{
	int w = 12;
	int h = 8;
	int i, j;

	i = 0;
	while (i < h + 1)
	{
		int k = 0;
		while (k++ < 6)
		{
			j = 0;
			while (j < w)
			{
				int c = 30 + j + i * w;
				int l = 0;
				printf(" ");
				while (l++ < 8)
					printf("%c", c);
				printf(" ");
				j++;
			}
			printf("\n");
		}
		i++;
	}
	return (0);
}
