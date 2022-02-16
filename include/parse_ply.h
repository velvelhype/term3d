/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ply.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:40:51 by tyamagis          #+#    #+#             */
/*   Updated: 2022/02/16 22:51:25 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLY_H
# define PLY_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_face
{
	int	v1;
	int	v2;
	int	v3;
} t_face;

typedef struct s_vertex
{
	float	x;
	float	y;
	float	z;
} t_vertex;

typedef struct s_ply
{
	int			elem_vertexes;
	int			elem_faces;
	t_vertex	*vertexes;
	t_face		*faces;
} t_ply;

t_ply	*parse_ply(char *filename);
void	*set_vertexes(t_ply *ply, FILE *f_stream);
void	*set_faces(t_ply *ply, FILE *f_stream);
void	*poly_to_tri(t_ply *ply, int n, FILE **f_stream);

#endif