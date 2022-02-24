#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int	main()
{
	char	*term3d = "/Users/tyamagis/term_3d_kamori/term3d";
	char	*f0[] = {term3d,
		"/Users/tyamagis/term_3d_kamori/ply_files/invalid_files/00_dup_face.ply",
		NULL};
	char	*f1[] = {term3d,
		"/Users/tyamagis/term_3d_kamori/ply_files/invalid_files/01_dup_vtx.ply",
		NULL};
	char	*f2[] = {term3d,
		"/Users/tyamagis/term_3d_kamori/ply_files/invalid_files/02_invalid_face.ply",
		NULL};
	char	*f3[] = {term3d,
		"/Users/tyamagis/term_3d_kamori/ply_files/invalid_files/03_invalid_vertex.ply",
		NULL};
	char	*f4[] = {term3d,
		"/Users/tyamagis/term_3d_kamori/ply_files/invalid_files/04_few_vtx_in_face.ply",
		NULL};
	char	*f5[] = {term3d,
		"/Users/tyamagis/term_3d_kamori/ply_files/invalid_files/05_large_coordinates.ply",
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
	char	*f10[] = {term3d,
		"/Users/tyamagis/term_3d_kamori/ply_files/invalid_files/10_same_vtx_in_face.ply",
		NULL};
	char **tests[12];
	tests[0] = f0;
	tests[1] = f1;
	tests[2] = f2;
	tests[3] = f3;
	tests[4] = f4;
	tests[5] = f5;
	tests[6] = f6;
	tests[7] = f7;
	tests[8] = f8;
	tests[9] = f9;
	tests[10] = f10;
	tests[11] = NULL;

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
