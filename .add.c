/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:01:10 by tyamagis          #+#    #+#             */
/*   Updated: 2022/02/20 21:26:24 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/term3d.h"

void	set_key_input();
void	calc_cam_pos();
void	calc_screen();

void	show_usage(t_term *tm)
{
	printf("\n\n==============\n=   term3d   =\n==============\n\n");
	printf("file : %s\n", tm->filename);
	// KEY ASSIGN
	printf("KEY ASSIGN\n");
	return ;
}

/* ==== */
/* test */
/* ==== */
int	main(void)
{
	t_term	tm;
	// SHOW_USAGE() TEST
	printf("show_usage() test");
	show_usage();

	// CALC_CAM_POS() TEST
	// CALC_SCARREN() TEST
	// SET_KEY_INPUT() TEST
	return (0);
}
