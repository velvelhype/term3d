/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:03:14 by tyamagis          #+#    #+#             */
/*   Updated: 2022/02/21 00:01:20 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/term3d.h"
#include "./include/parse_ply.h"

int	set_char(t_term *tm, float d, char *data)
{
	int		ret;
	int		round;

	ret = 1;
	round = (int)(d * tm->charset_size);
	if (round >= 0 && round < tm->threshold)
	{
		memset(data, tm->charset[round], 1);
		memset(data + 1, ' ', 1);
	}
	else if (round >= tm->threshold)
		memset(data, tm->charset[round - tm->threshold + 1], 2);
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
			ret += set_char(tm, d, data);
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

char	*change_size(t_term *tm, char **data, int size)
{
	size_t	data_size;

	tm->width = size;
	tm->height = size;
	tm->lim_x = size * 0.5;
	tm->lim_y = size * -0.5;
	data_size = (size * 2 + 1) * tm->height + 1;
	if (*data != NULL)
	{
		free(*data);
		*data = NULL;
	}
	*data = (char *)malloc(data_size);
	if (*data == NULL)
		exit_me(ERR_MALLOC);
	return (*data);
}

void	loop_draw(t_term *tm, t_ply *ply)
{
	char			*data;
	int				win_size;
	struct winsize	w;

	data = malloc(1);
	while (1)
	{
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		win_size = w.ws_col * 0.5;
		if (win_size > w.ws_row)
			win_size = w.ws_row;
		if (win_size != tm->height)
			data = change_size(tm, &data, win_size);
		if (!calc_data(tm, ply, data))
			exit_me(NO_DISPLAY);
		fprintf(stderr, "\033[2J\033[2H");
		fprintf(stderr, "%s", data);
		if (tm->deg > 360)
			tm->deg -= 360;
		tm->deg += 0.07;
		usleep(50000);
	}
	return ;
}
