/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:03:14 by tyamagis          #+#    #+#             */
/*   Updated: 2022/02/19 16:50:39 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/term3d.h"
#include "./include/parse_ply.h"

int	set_char(float d, char *data)
{
	int	ret;

	if (d >= 0)
	{
		memset(data, '+', 1);
		memset(data + 1, '.', 1);
		ret = 1;
	}
	else
	{
		memset(data, ' ', 2);
		ret = 0;
	}
	return (ret);
}

int	calc_data(t_term *tm, t_ply *ply, char *data)
{
	float	d;
	int		x;
	int		y;
	int		ret;

	ret = 0;
	y = tm->lim_x;
	while (y > tm->lim_y)
	{
		x = tm->lim_y;
		while (x < tm->lim_x)
		{
			d = is_colided(x, y, tm, ply);
			ret += set_char(d, data);
			data += 2;
			x++;
		}
		memset(data, '\n', 1);
		data++;
		y--;
	}
	memset(data, '\0', 1);
	return (ret);
}

void	loop_draw(t_term *tm, t_ply *ply)
{
	size_t	data_size;
	char	*data;

	data_size = (tm->width * 2 + 1) * tm->height + 1;
	data = (char *)malloc(data_size);
	if (data == NULL)
		exit_me();
	while (1)
	{
		if (!calc_data(tm, ply, data))
			exit_me();
		fprintf(stderr, "\033[2J\033[2H");
		fprintf(stderr, "%s", data);
		if (tm->deg > 360)
			tm->deg -= 360;
		tm->deg += 0.4;
		usleep(50000);
	}
	return ;
}
