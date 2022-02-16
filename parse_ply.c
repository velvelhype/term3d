/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ply.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:56:58 by tyamagis          #+#    #+#             */
/*   Updated: 2022/02/16 16:02:10 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ply.h"

t_ply	*parse_ply(char *filename)
{
	t_ply	*ply;
	FILE	*stream;
	char	*str;

	ply = (t_ply *)malloc(sizeof(t_ply));
	if (ply == NULL)
		return (NULL);
	stream = fopen(filename, "r");
	while (strcmp(str, "end_header"))
	{
		fscanf(stream, "%s", str);
		if (strcmp(str, "vertex") == 0)
			fscanf(stream, "%d", &ply->elem_vertex);
		else if (strcmp(str, "face") == 0)
			fscanf(stream, "%d", &ply->elem_face);
	}
	return (ply);
}

/* test */
int	main(int ac, char **av)
{
	t_ply	*ply;
	int		i;

	ply = parse_ply(av[ac - 1]);
	printf("vertex : %d, face : %d\n", ply->elem_vertex, ply->elem_face);
	/*
	printf("elem_vertex : %d, elem_face : %d\n", ply->elem_vertex, ply->elem_face);
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
	*/
	return (0);
}
