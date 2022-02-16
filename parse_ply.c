/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ply.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:56:58 by tyamagis          #+#    #+#             */
/*   Updated: 2022/02/16 22:54:08 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/parse_ply.h"

void	*poly_to_tri(t_ply *ply_info, int n, FILE **f_stream)
{
	t_face	*new_faces;
	int		i;
	int		new_elem;
	int		v1;
	int		v3;

	new_elem = ply_info->elem_faces + n - 3;
	new_faces = (t_face *)malloc(sizeof(t_face) * new_elem);
	// add NULL check later.
	i = 0;
	while (i < ply_info->elem_faces)
	{
		new_faces[i].v1 = ply_info->faces[i].v1;
		new_faces[i].v2 = ply_info->faces[i].v2;
		new_faces[i].v3 = ply_info->faces[i].v3;
		i++;
	}
	free(ply_info->faces);
	ply_info->faces = new_faces;
	ply_info->elem_faces = new_elem;
	fscanf(*f_stream, "%d %d %d", &new_faces[i].v1, &new_faces[i].v2, &new_faces[i].v3);
	v1 = new_faces[i].v1;
	v3 = new_faces[i].v3;
	i++;
	while (i < new_elem)
	{
		new_faces[i].v1 = v1;
		new_faces[i].v2 = v3;
		fscanf(*f_stream, "%d", &new_faces[i].v3);
		i++;
	}
	return (new_faces);
}

void	*set_faces(t_ply *ply_info, FILE *f_stream)
{
	int		i;
	int		old_elem_face;
	int		num_of_vtx;
	t_face	*faces;

	faces = ply_info->faces;
	i = 0;
	old_elem_face = ply_info->elem_faces;
	while (i++ < old_elem_face)
	{
		fscanf(f_stream, "%d", &num_of_vtx);
		if (num_of_vtx == 3)
		{
			fscanf(f_stream, "%d %d %d", &faces->v1, &faces->v2, &faces->v3);
			faces++;
		}
		else
			poly_to_tri(ply_info, num_of_vtx, &f_stream);
	}
	return (ply_info->faces);
}

void	*set_vertexes(t_ply *ply_info, FILE *f_stream)
{
	int			i;
	t_vertex	*vtx;

	vtx = ply_info->vertexes;
	i = 0;
	while (i++ < ply_info->elem_vertexes)
	{
		fscanf(f_stream, "%f %f %f", &vtx->x, &vtx->y, &vtx->z);
		vtx++;
	}
	return (ply_info->vertexes);
}

t_ply	*parse_ply(char *filename)
{
	t_ply	*ply_info;
	char	str[100];
	FILE	*f_stream;

	f_stream = fopen(filename, "r");
	ply_info = (t_ply *)malloc(sizeof(t_ply));
	// add NULL check later.
	while (strcmp(str, "end_header"))
	{
		fscanf(f_stream, "%s", str);
		if (strcmp(str, "vertex") == 0)
			fscanf(f_stream, "%d", &ply_info->elem_vertexes);
		else if (strcmp(str, "face") == 0)
			fscanf(f_stream, "%d", &ply_info->elem_faces);
	}
	ply_info->vertexes = (t_vertex *)malloc(sizeof(t_vertex) * ply_info->elem_vertexes);
	ply_info->faces = (t_face *)malloc(sizeof(t_face) * ply_info->elem_faces);
	// add NULL check later.
	set_vertexes(ply_info, f_stream);
	set_faces(ply_info, f_stream);
	return (ply_info);
}

/* test
int	main(int ac, char **av)
{
	t_ply	*ply_info;
	FILE	*f_stream;
	char	*filename;
	int		i;

	filename = av[ac - 1];
	ply_info = set_elem(filename);
	printf("vertex : %d, face : %d\n", ply_info->elem_vertexes, ply_info->elem_faces);
	printf("\nvertex list : \n");
	i = 0;
	while (i < ply_info->elem_vertexes)
	{
		printf("(%f, %f, %f)\n", ply_info->vertexes[i].x, ply_info->vertexes[i].y, ply_info->vertexes[i].z);
		i++;
	}
	
	printf("\nface list : \n");
	i = 0;
	while (i < ply_info->elem_faces)
	{
		printf("%d idx : %d %d %d\n", i, ply_info->faces[i].v1, ply_info->faces[i].v2, ply_info->faces[i].v3);
		i++;
	}
	
	return (0);
}
*/
