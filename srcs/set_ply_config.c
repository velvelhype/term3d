/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ply_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 22:08:11 by tyamagis          #+#    #+#             */
/*   Updated: 2022/02/24 22:42:47 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_ply.h"
#include "term3d.h"

void	*recreate_faces(t_ply *ply_info, t_face *old, int *read, int elm)
{
	int		i;
	t_face	*new;

	new = (t_face *)malloc(sizeof(t_face) * elm);
	if (new == NULL)
		exit_with_msg(ERR_MALLOC);
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
	int		v1;
	int		v3;
	t_face	*faces;

	new_elm = ply_info->elem_faces + vtx - 3;
	faces = recreate_faces(ply_info, ply_info->faces, read, new_elm);
	if (fscanf(f_stream, "%99d %99d %99d", &faces[*read].v1, &faces[*read].v2, \
			&faces[*read].v3) != 3)
		exit_with_msg(ERR_FMT);
	v1 = faces[*read].v1;
	v3 = faces[*read].v3;
	(*read)++;
	while (--vtx >= 3)
	{
		faces[*read].v1 = v1;
		faces[*read].v2 = v3;
		if (!fscanf(f_stream, "%99d", &faces[*read].v3))
			exit_with_msg(ERR_FMT);
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
		if (!fscanf(f_stream, "%99d", &num_of_vtx))
			exit_with_msg(ERR_FMT);
		if (num_of_vtx == 3)
		{
			if (fscanf(f_stream, "%99d %99d %99d", &faces[i].v1, \
					&faces[i].v2, &faces[i].v3) != 3)
				exit_with_msg(ERR_FMT);
			i++;
		}
		else
		{
			poly_to_tri(ply_info, f_stream, &i, num_of_vtx);
		}
	}
	return (ply_info->faces);
}

void	*set_vertexes(t_ply *ply, FILE *f_stream)
{
	int			i;
	t_vector	*vtx;

	ply->vertexes = (t_vector *)malloc(sizeof(t_vector) * ply->elem_vertexes);
	ply->faces = (t_face *)malloc(sizeof(t_face) * ply->elem_faces);
	if (ply->vertexes == NULL || ply->faces == NULL)
		exit_with_msg(ERR_MALLOC);
	vtx = ply->vertexes;
	i = 0;
	while (i++ < ply->elem_vertexes)
	{
		if (fscanf(f_stream, "%99f %99f %99f", &vtx->x, &vtx->y, &vtx->z) != 3)
			exit_with_msg(ERR_FMT);
		vtx->x *= DEF_ZOOM;
		vtx->y *= DEF_ZOOM;
		vtx->z *= DEF_ZOOM;
		vtx++;
	}
	return (ply->vertexes);
}
