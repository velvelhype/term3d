/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ply.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:56:58 by tyamagis          #+#    #+#             */
/*   Updated: 2022/02/18 15:28:23 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/parse_ply.h"

void	*recreate_faces(t_ply *ply_info, t_face *old, int *read, int elm)
{
	int		i;
	t_face	*new;

	new = (t_face *)malloc(sizeof(t_face) * elm);
	if (new == NULL)
		return (NULL); // or replace EXIT;
	i = 0;
	while (i < *read)
	{
		new[i].v1 = old[i].v1;
		new[i].v2 = old[i].v2;
		new[i].v3 = old[i].v3;
		i++;
	}
	free(old);
	ply_info->faces = new;
	ply_info->elem_faces = elm;
	return (new);
}

void	*poly_to_tri(t_ply *ply_info, FILE *f_stream, int *read, int vtx)
{
	int		new_elm;
	int		i;
	int		v1;
	int		v3;
	t_face	*faces;

	new_elm = ply_info->elem_faces + vtx - 3;
	faces = recreate_faces(ply_info, ply_info->faces, read, new_elm);
	fscanf(f_stream, "%d %d %d", &faces[*read].v1, &faces[*read].v2, &faces[*read].v3);
	v1 = faces[*read].v1;
	v3 = faces[*read].v3;
	(*read)++;
	while (--vtx >= 3)
	{
		faces[*read].v1 = v1;
		faces[*read].v2 = v3;
		fscanf(f_stream, "%d", &faces[*read].v3);
		v3 = faces[*read].v3;
		(*read)++;
	}
	return (faces);
}

void	*set_faces(t_ply *ply_info, FILE *f_stream)
{
	int		i;
	int		num_of_vtx;
	t_face	*faces;

	faces = ply_info->faces;
	i = 0;
	while (i < ply_info->elem_faces)
	{
		fscanf(f_stream, "%d", &num_of_vtx); // GET number of Vertex
		if (num_of_vtx == 3)
		{
			fscanf(f_stream, "%d %d %d", &faces[i].v1, &faces[i].v2, &faces[i].v3);
			i++;
		}
		else
		{
			poly_to_tri(ply_info, f_stream, &i, num_of_vtx);
		}
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
	printf("first elem_face : %d\n", ply_info->elem_faces);
	set_vertexes(ply_info, f_stream);
	set_faces(ply_info, f_stream);
	return (ply_info);
}

// test
int	main(int ac, char **av)
{
	t_ply	*ply_info;
	FILE	*f_stream;
	char	*filename;
	int		i;

	filename = av[ac - 1];
	ply_info = parse_ply(filename);
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
//*/
