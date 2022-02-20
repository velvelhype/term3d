#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int	main()
{
	char *nop[] = 
	{"/Users/kazukimori/Codes/term3d/my_term3d/term3d",
	"/Users/kazukimori/Codes/term3d/my_term3d/obj/nop.ply",
	NULL};

	char *cube[] =
	{"/Users/kazukimori/Codes/term3d/my_term3d/term3d",
	"/Users/kazukimori/Codes/term3d/my_term3d/obj/cube.ply",
	NULL};

	char *torus_and_cube[] =
	{"/Users/kazukimori/Codes/term3d/my_term3d/term3d",
	"/Users/kazukimori/Codes/term3d/my_term3d/obj/torus_and_cube.ply",
	NULL};

	//
	char **tests[5];
	tests[0] = nop;
	tests[1] = cube;
	tests[2] = torus_and_cube;
	tests[4] = NULL;

	int i = 0;
	while(tests[i])
	{
		int f = fork();
		if (f == 0)
		{
			execve(*tests[i], tests[i], NULL);
		}
		else
		{
			sleep(3);
			kill(f, SIGTERM);
		}
		i++;
	}
}
