#include <time.h>
#include <stdio.h>
#include <pthread.h>

int	calc(int a, int b)
{
	int	ret;

	ret = (a * a * a) / (b * b * b);
	return (ret);
}

void	mthread(void)
{

}

int	main(void)
{
	printf("no therad calc\n");
	
