#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	FILE		*f_stream;
	struct stat	st;
	char		*filedata;
	char		*line;
	size_t		len;
	size_t		size_line;

	stat(av[1], &st);
	printf("%llu\n", st.st_size);
	filedata = (char *)malloc(sizeof(char) * st.st_size);
	char *tmp = filedata;
	f_stream = fopen(av[1], "r");
	size_line = 1;
	while (size_line != -1)
	{
		int i = 0;
		printf("%d\n", i);
		i++;
		size_line = getline(&filedata, &len, f_stream);
		if (size_line == -1)
			break ;
		filedata += size_line;
	}
	printf("%s", tmp);
}
