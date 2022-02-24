/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:03:14 by tyamagis          #+#    #+#             */
/*   Updated: 2022/02/24 23:15:48 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term3d.h"
#include "parse_ply.h"
#include "vector.h"

void	set_char(t_term *tm, float rflct, char *pxl_data)
{
	int	round;

	round = (int)(rflct * tm->charset_size);
	if (round > 0 && round < tm->threshold)
	{
		*pxl_data = tm->charset[round];
		*(pxl_data + 1) = ' ';
	}
	else if (round >= tm->threshold)
		memset(pxl_data, tm->charset[round - tm->threshold + 1], 2);
	else
		memset(pxl_data, ' ', 2);
	return ;
}

void	rotate_vtx(t_term *tm, t_ply *ply)
{
	int			i;
	t_vector	*v;
	float		new_x;
	float		new_z;

	i = 0;
	while (i < ply->elem_vertexes)
	{
		v = &ply->vertexes[i];
		new_x = v->x * tm->rotate_cos - v->z * tm->rotate_sin;
		new_z = v->x * tm->rotate_sin + v->z * tm->rotate_cos;
		v->x = new_x;
		v->z = new_z;
		i++;
	}
	return ;
}

void	calc_pxl_data(t_term *tm, t_ply *ply, char *pxl_data)
{
	float	rflct;
	int		x;
	int		y;

	rotate_vtx(tm, ply);
	y = tm->size;
	while (y-- > 0)
	{
		x = 0;
		while (x < tm->size)
		{
			rflct = calc_crossing_eye_dir_and_face(x - tm->lim,
					y - tm->lim, tm, ply);
			set_char(tm, rflct, pxl_data);
			pxl_data += 2;
			x++;
		}
		*pxl_data++ = '\n';
	}
	*pxl_data = '\0';
	return ;
}

void	update_win_size(t_term *tm, char **pxl_data)
{
	size_t			data_size;
	int				win_size;
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	win_size = w.ws_col * 0.5;
	if (win_size > w.ws_row)
		win_size = w.ws_row;
	if (win_size != tm->size)
	{
		tm->size = win_size;
		tm->lim = win_size * 0.5;
		data_size = (win_size * 2 + 1) * win_size + 1;
		if (*pxl_data != NULL)
		{
			free(*pxl_data);
			*pxl_data = NULL;
		}
		*pxl_data = (char *)malloc(data_size);
		if (*pxl_data == NULL)
			exit_with_msg(ERR_MALLOC);
	}
	return ;
}

void	loop_draw(t_term *tm, t_ply *ply)
{
	char	*pxl_data;

	pxl_data = malloc(1);
	while (1)
	{
		update_win_size(tm, &pxl_data);
		calc_pxl_data(tm, ply, pxl_data);
		fprintf(stderr, "\033[2J\033[2H");
		fprintf(stderr, "%s", pxl_data);
		usleep(20000);
	}
	return ;
}
