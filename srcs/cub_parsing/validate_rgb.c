/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbounor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:00:12 by lbounor           #+#    #+#             */
/*   Updated: 2022/11/10 16:17:50 by lbounor          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	verif_rgb(char **rgb_split, t_data *data)
{
	if (split_size(rgb_split) == 3)
	{
		data->map_data.color.r = ft_atoi(rgb_split[0]);
		data->map_data.color.g = ft_atoi(rgb_split[1]);
		data->map_data.color.b = ft_atoi(rgb_split[2]);
		if ((data->map_data.color.r < 0 || data->map_data.color.r > 255)
			|| (data->map_data.color.g < 0 || data->map_data.color.g > 255)
			|| (data->map_data.color.b < 0 || data->map_data.color.b > 255))
			return (1);
		return (0);
	}
	return (1);
}

static void	convert_to_hex(t_data *data, int i)
{
	unsigned long	tmp;

	if (i == 0)
		data->map_data.f = ((data->map_data.color.r & 0xff) << 16)
			+ ((data->map_data.color.g & 0xff) << 8)
			+ (data->map_data.color.b & 0xff);
	if (i == 1)
		data->map_data.c = ((data->map_data.color.r & 0xff) << 16)
			+ ((data->map_data.color.g & 0xff) << 8)
			+ (data->map_data.color.b & 0xff);
}

int	validate_rgb(t_data *data)
{
	char	**rgb_split;
	int		i;

	i = 0;
	while (data->map_data.rgb[i])
	{
		rgb_split = ft_split(data->map_data.rgb[i], ',');
		if (!rgb_split)
			return (1);
		if (verif_rbg(rgb_split, data) == 1)
		{
			ft_free_char(rgb_split);
			return (1);
		}
		convert_to_hex(data, i);
		ft_free_char(rgb_split);
		i++;
	}
	return (0);
}
