/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ply.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 20:06:36 by tyamagis          #+#    #+#             */
/*   Updated: 2022/02/24 00:29:21 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * get file size
 * malloc to save file
 * savefile
 *
 * check header
 * check coordinate list
 * check face list
 *
 * go to parse
 */

#include <sys/stat.h>
#include <stdio.h>

void	check_ply_header;
void	check_ply_vtxs;
void	check_ply_faces;

void	x_check_ply(char *filename)
{
	FILE		*f_stream;
	struct stat	st;
	char		*filedata;
	char		*line;
	size_t		len;
	size_t		size_line;

	if (stat(filename, &st))
		exit_w_msg(ERR_F_READ);
	filedata = (char *)malloc(sizeof(char) * st.st_size);
	if (filedata == NULL)
		exit_w_msg(ERR_MALLOC)
	f_stream = fopen(filename, "r");
	if (f_stream == NULL)
		exit_w_msg(ERR_F_READ);
	size_line = 0;
	while (size_line != -1)
	{
		size_line = getline(&line, &len, f_stream);
		line += size_line;
