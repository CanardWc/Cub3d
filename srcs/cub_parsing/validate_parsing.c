/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbounor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:06:57 by lbounor           #+#    #+#             */
/*   Updated: 2022/11/16 17:32:16 by lbounor          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	ft_exit(char *s, t_data *data)
{
	write(2, s, ft_strlen(s));
	ft_free_char(data->map_data.xpm);
	ft_free_char(data->map_data.rgb);
	ft_free_int(data->map_data.map);
	exit(1);
}

/*
 *	A appeler apres : main_parsing(char *file, t_data *data) ;
 *	Va verifier la map, convert rgb et charger .xpm
*/
void	validate_parsing(t_data *data)
{
	if (validate_xpm() == 1)
		ft_exit("Error\nCannot load textures\n", data);
	if (validate_rgb() == 1)
		ft_exit("Error\nCannot load colors\n", data);
	if (validate_map() == 1)
		ft_exit("Error\nInvalid map\n", data);
}

static int	check_border(int i, t_data *data)
{
	int	j;

	j = 0;
	while (data->map_data.map[i][j] < data->map_data.width)
	{
		if (data->map_data.map[i][j] != 1 && data->map_data.map[i][j] != -1)
			return (1);
		i++;
	}
	return (0);
}

int	validate_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map_data.map[i] < data->map_data.height)
	{
		j = 0;
		if (i == 0)
			if (check_border(0, data) == 1)
				return (1);
		while (data->map_data.map[i][j] < data->map_data.width)
		{
			if (is_closed(i, j) == 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
