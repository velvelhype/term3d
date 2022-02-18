#include <time.h>
#include <stdio.h>
#include <pthread.h>

typedef struct s_data
{
	int	start;
	int	end;
} t_data;

long double	calc(long double a, long double b)
{
	long double	div;
	long double	pow_a;
	long double	pow_b;

	while (a++ < 100000)
	{
		while (b++ < 100000)
		{
			div = a / b;
			pow_a = a * a;
			pow_b = b * b;
			div = pow_a / pow_b / div;
		}
	}
	return (div);
}

int	main(void)
{
	long double	ld[2];
	clock_t		start, end;
	int			num = 2; // thread vars 
	pthread_t	th[num];
	t_data		data[2];

	/*
	 * without threads -----
	 */
	printf("\ncalc without therads\n");
	ld[0] = 0;
	ld[1] = 1;
	start = clock();
	calc(ld[0], ld[1]);
	end = clock();
	printf("Time : %lu\n", end - start);

	/*
	 * with threads -----
	 */
	ld[0] = 0;
	ld[1] = 1;
	printf("\ncalc with threads\n");

	start = clock();
	// create threads
	pthread_create(&th[0], NULL, calc_th, &data[0]);
	pthread_create(&th[1], NULL, calc_th, &data[1]);
	data[0].start = 0;
	data[0].end = 49999;
	data[1].start = 50000;
	data[1].end = 99999;
	end = clock();
	printf("Time : %lu\n", end - start);

	start = clock();
	// calc
	end = clock();
	printf("Time : %lu\n", end - start);

	return (0);
}
