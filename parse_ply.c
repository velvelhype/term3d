/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ply.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:56:58 by tyamagis          #+#    #+#             */
/*   Updated: 2022/02/24 22:41:45 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/parse_ply.h"
#include "./include/term3d.h"

void	check_ply_header(t_ply *p, FILE *f_stream)
{
	char	str[100];
	int		ret;

	ret = fscanf(f_stream, "%99s", str);
	if (strcmp(str, "ply"))
		exit_with_msg(ERR_FMT);
	while (strcmp(str, "end_header"))
	{
		fscanf(f_stream, "%99s", str);
		if (strcmp(str, "vertex") == 0)
			ret += fscanf(f_stream, "%99d", &p->elem_vertexes);
		else if (strcmp(str, "face") == 0)
			ret += fscanf(f_stream, "%99d", &p->elem_faces);
	}
	if (ret != 3)
		exit_with_msg(ERR_FMT);
	return ;
}

t_ply	*parse_ply(char *filename)
{
	t_ply	*ply_info;
	FILE	*f_stream;

	f_stream = fopen(filename, "r");
	ply_info = (t_ply *)malloc(sizeof(t_ply));
	if (f_stream == NULL || ply_info == NULL)
		exit_with_msg(ERR_ARG);
	check_ply_header(ply_info, f_stream);
	set_vertexes(ply_info, f_stream);
	set_faces(ply_info, f_stream);
	return (ply_info);
}
