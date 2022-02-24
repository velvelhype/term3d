#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int	main()
{
	char	*term3d = "/Users/tyamagis/term_3d_kamori/term3d";
	char	*f2[] = {term3d,
		"/Users/tyamagis/term_3d_kamori/ply_files/invalid_files/02_invalid_face.ply",
		NULL};
	char	*f6[] = {term3d,
		"/Users/tyamagis/term_3d_kamori/ply_files/invalid_files/06_many_vtx_in_face.ply",
		NULL};
	char	*f7[] = {term3d,
		"/Users/tyamagis/term_3d_kamori/ply_files/invalid_files/07_no_face.ply",
		NULL};
	char	*f8[] = {term3d,
		"/Users/tyamagis/term_3d_kamori/ply_files/invalid_files/08_no_ply.ply",
		NULL};
	char	*f9[] = {term3d,
		"/Users/tyamagis/term_3d_kamori/ply_files/invalid_files/09_no_vertex.ply",
		NULL};
	char **tests[7];
	tests[0] = f2;
	tests[1] = f6;
	tests[2] = f7;
	tests[3] = f8;
	tests[4] = f9;
	tests[5] = NULL;

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
