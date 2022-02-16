/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ply.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:56:58 by tyamagis          #+#    #+#             */
/*   Updated: 2022/02/16 18:17:02 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ply.h"

void	*poly_to_tri(t_ply *ply, int n, FILE **f_stream)
{
	t_face	*new_faces;
	int		i;
	int		new_elem;
	int		v1;
	int		v3;

	new_elem = ply->elem_face + n - 3;
	new_faces = (t_face *)malloc(sizeof(t_face) * new_elem);
	// add NULL check later.
	i = 0;
	while (i < ply->elem_face)
	{
		new_faces[i].v1 = ply->faces[i].v1;
		new_faces[i].v2 = ply->faces[i].v2;
		new_faces[i].v3 = ply->faces[i].v3;
		i++;
	}
	free(ply->faces);
	ply->faces = new_faces;
	ply->elem_face = new_elem;
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

void	*set_faces(t_ply *ply, FILE *f_stream)
{
	int		i;
	int		old_elem_face;
	int		num_of_vtx;
	t_face	*faces;

	faces = ply->faces;
	i = 0;
	old_elem_face = ply->elem_face;
	while (i++ < old_elem_face)
	{
		fscanf(f_stream, "%d", &num_of_vtx);
		if (num_of_vtx == 3)
		{
			fscanf(f_stream, "%d %d %d", &faces->v1, &faces->v2, &faces->v3);
			faces++;
		}
		else
			poly_to_tri(ply, num_of_vtx, &f_stream);
	}
	return (ply->faces);
}

void	*set_vertexes(t_ply *ply, FILE *f_stream)
{
	int			i;
	t_vertex	*vtx;

	vtx = ply->vertexes;
	i = 0;
	while (i++ < ply->elem_vertex)
	{
		fscanf(f_stream, "%f %f %f", &vtx->x, &vtx->y, &vtx->z);
		vtx++;
	}
	return (ply->vertexes);
}

t_ply	*set_elem(FILE *f_stream)
{
	t_ply	*ply;
	char	str[100];

	ply = (t_ply *)malloc(sizeof(t_ply));
	// add NULL check later.
	while (strcmp(str, "end_header"))
	{
		fscanf(f_stream, "%s", str);
		if (strcmp(str, "vertex") == 0)
			fscanf(f_stream, "%d", &ply->elem_vertex);
		else if (strcmp(str, "face") == 0)
			fscanf(f_stream, "%d", &ply->elem_face);
	}
	ply->vertexes = (t_vertex *)malloc(sizeof(t_vertex) * ply->elem_vertex);
	ply->faces = (t_face *)malloc(sizeof(t_face) * ply->elem_face);
	// add NULL check later.
	set_vertexes(ply, f_stream);
	set_faces(ply, f_stream);
	return (ply);
}

/* test */
int	main(int ac, char **av)
{
	t_ply	*ply;
	FILE	*f_stream;
	char	*filename;
	int		i;

	filename = av[ac - 1];
	f_stream = fopen(filename, "r");
	ply = set_elem(f_stream);
	printf("vertex : %d, face : %d\n", ply->elem_vertex, ply->elem_face);
	printf("\nvertex list : \n");
	i = 0;
	while (i < ply->elem_vertex)
	{
		printf("(%f, %f, %f)\n", ply->vertexes[i].x, ply->vertexes[i].y, ply->vertexes[i].z);
		i++;
	}
	
	printf("\nface list : \n");
	i = 0;
	while (i < ply->elem_face)
	{
		printf("%d idx : %d %d %d\n", i, ply->faces[i].v1, ply->faces[i].v2, ply->faces[i].v3);
		i++;
	}
	
	return (0);
}
