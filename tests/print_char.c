// THIS PROGRAM DISPLAYS BLOCKS STRUCTURED BY CHAR.

#include <stdio.h>

int main(void)
{
	int	w = 40;
	int	h = 5;
	int	c = 32; // 32-126 is printed.

	for (int c = 32; c < 127; c++)
	{
		printf("%d\n", c);
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
				printf("%c", c);
			printf("\n");
		}
		printf("\n\n");
	}
	return (0);
}
