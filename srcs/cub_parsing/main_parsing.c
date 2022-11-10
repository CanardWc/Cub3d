/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbounor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:03:31 by Leo               #+#    #+#             */
/*   Updated: 2022/11/10 13:34:21 by lbounor          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	ft_exit(char *s, int fd, t_data *data)
{
	if (fd < 0)
		close(fd);
	write(2, s, ft_strlen(s));
	ft_free_char(data->map_data.xpm);
	ft_free_char(data->map_data.rgb);
	ft_free_int(data->map_data.map);
	exit(1);
}

int	main_parsing(char *file, t_data *data)
{
	int	is_exist;
	int	fd;

	is_exist = access(file, R_OK);
	if (!check_ext(file, ".cub") || is_exist != 0)
		ft_exit("Error\nInvalid extension\n", -1, data);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_exit("Error\nCannot open the map\n", fd, data);
	if (parse_texture_xpm(fd, data) == 1)
		ft_exit("Error\nInvalid information\n", fd, data);
	if (parse_texture_rgb(fd, data) == 1)
		ft_exit("Error\nInvalid information\n", fd, data);
	if (parse_map(fd, data) == 1)
		ft_exit("Error\nInvalid map\n", fd, data);
	close (fd);
	return (0);
}
