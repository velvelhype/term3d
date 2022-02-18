#include <time.h>
#include <stdio.h>
#include <pthread.h>

int	calc(int a, int b)
{
	int	ret;

	ret = (a * a * a) / (b * b * b);
	return (ret);
}

int	main(void)
{
	int a = 0;
	int b = 1;
	clock_t	start, end;

	printf("calc without therads\n");
	// timer start
	while (a < 100000)
		calc(a++, b++);
	// timer end
	// print time

	a = 0;
	b = 1;
	printf("calc with threads\n");
	// timer start
	// create threads
	// timer end
	// print time
	//
	// timer start
	// calc()
	// timer end
	// print time
	return (0);
}
