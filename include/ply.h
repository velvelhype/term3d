/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ply.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:40:51 by tyamagis          #+#    #+#             */
/*   Updated: 2022/02/16 15:56:22 by tyamagis         ###   ########.fr       */
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
	int			elem_vertex;
	int			elem_face;
	t_vertex	*vertexes;
	t_face		*faces;
} t_ply;

#endif
