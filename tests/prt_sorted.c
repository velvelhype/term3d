#include <stdio.h>

int main(void)
{
	int	h = 10;
	char *set = " -.`'_,:~\";^!*/r()+<>\\=?|lc]i[j7Ltvszf1Jx}CTY{nuFyoI\%23aehk45wSVZ$XGdPpbmqEU&69AOK0gH8D#QR@MBWN";
	char *set16 = " -',~^*r=ctxFX8N";

	int i = 0;
	while (i++ < h)
		printf("%s\n", set);
	i = 0;
	while (i++ < h)
	{
		int j = 0;
		while (set16[j] != '\0')
		{
			int k = 0;
			while (k++ < 4)
				printf("%c", set16[j]);
			j++;
		}
		printf("\n");
	}

	return (0);
}
