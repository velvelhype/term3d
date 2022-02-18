/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ply.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:40:51 by tyamagis          #+#    #+#             */
/*   Updated: 2022/02/18 15:26:48 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLY_H
# define PLY_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../vector.h"


typedef struct s_face
{
	int	v1;
	int	v2;
	int	v3;
} t_face;

typedef struct s_ply
{
	int			elem_vertexes;
	int			elem_faces;
	t_vector	*vertexes;
	t_face		*faces;
} t_ply;

t_ply	*parse_ply(char *filename);
void	*set_vertexes(t_ply *ply, FILE *f_stream);
void	*set_faces(t_ply *ply, FILE *f_stream);
void	*poly_to_tri(t_ply *ply, FILE *f_stream, int *read, int vtx);
void	*recreate_faces(t_ply *ply_info, t_face *old, int *read, int elm);

#endif
