/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbounor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:13:14 by lbounor           #+#    #+#             */
/*   Updated: 2022/11/10 12:35:49 by lbounor          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	set_values_player_dir(double d_x, double d_y, t_data *data)
{
	data->dir.x = d_x;
	data->dir.y = d_y;
}

static void	set_values_player_plane(double p_x, double p_y, t_data *data)
{
	data->rplane.x = p_x;
	data->rplane.y = p_y;
}

int	fill_pos_player(t_data *data, char *c, int i, int j)
{
	if (data->pos.x == 0 && data->pos.y == 0)
	{
		data->pos.x = i + 0.5;
		data->pos.y = j + 0.5;
		if (*c == 'N')
		{
			set_values_player_dir(0, -1, data);
			set_values_player_plane(0.80, 0, data);
		}
		else if (*c == 'S')
		{
			set_values_player_dir(0, 1, data);
			set_values_player_plane(-0.80, 0, data);
		}
		else if (*c == 'E')
		{
			set_values_player_dir(1, 0, data);
			set_values_player_plane(0, 0.8, data);
		}
		else if (*c == 'W')
		{
			set_values_player_dir(-1, 0, data);
			set_values_player_plane(0, -0.8, data);
		}
		*c = '0';
	}
	else
		return (1);
	return (0);
}
