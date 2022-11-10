/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leo <Leo@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:03:31 by Leo               #+#    #+#             */
/*   Updated: 2022/11/09 13:39:38 by Leo              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main_parsing(char *file, t_data *data)
{
	int	is_exist;
	int	fd;

	is_exist = access(file, R_OK);
	if (!check_ext(file, ".cub") || is_exist != 0)
		return (1); //ERROR
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1); //ERROR
	if (parse_texture_xpm(fd, data) == 1)
		return (1); //ERROR
	if (parse_texture_rgb(fd, data) == 1)
		return (1); //ERROR
	if (parse_map(fd, data) == 1)
		return (1); //ERROR
	close (fd);
	return (0);
}
