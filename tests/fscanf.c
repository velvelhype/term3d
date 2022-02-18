#include <stdio.h>

int main(int ac, char **av)
{
	FILE *f = fopen(av[ac -1], "r");
	char	s[1000];
	int		d;
	size_t	ret;
	ret = fscanf(f, "%d", &d);
	printf("%zu\n", ret);
	printf("%d", d);
	return (0);
}
