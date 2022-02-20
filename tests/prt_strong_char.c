// THIS PROGRAM DISPLAYS BLOCKS STRUCTURED BY CHAR.

#include <stdio.h>

int main(void)
{
	int	w = 10;
	int	h = 80;
	char	*set = "NBWM#QO089DEFPm"; // 32-126 is printed.

	int i = 0;
	while (i++ < h)
	{
		int j = 0;
		while (set[j] != '\0')
		{
			int k = 0;
			while (k++ < 6)
				printf("%c", set[j]);
			j++;
		}
		printf("\n");
	}

	printf("\n");
/*
	while (*set != '\0')
	{
		int i = 0;
		while (i++ < h)
		{
			int j = 0;
			while (j++ < w)
				printf("%c", *set);
			j = 5;
			printf("\t");
			while (j++ < w)
				printf("%c ", *set);
			printf("\n");
		}
		set++;
	}
*/
	return (0);
}
