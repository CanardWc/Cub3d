/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbounor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:04:10 by Leo               #+#    #+#             */
/*   Updated: 2022/11/10 12:21:02 by lbounor          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	fill_map_next(char *line, t_data *data)
{
	int		j;
	int		i;

	j = 0;
	while (h < data->map_data.height)
	{
		i = 0;
		while (i < data->map_data.width)
		{
			if (i < ft_strlen(line) && line[i] - '0' >= 0)
			{
				if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
					|| line[i] == 'E')
					if (fill_pos_player(data, &line[i], i, j) == 1)
						return (1);
				data->map_data.map[j][i] = line[i] - '0';
			}
			else
				data->map_data.map[j][i] = -1;
			i++;
		}
		j++;
	}
	return (0);
}

static int	fill_map(char *line, t_data *data)
{
	int		i;

	i = 0;
	if (!data->map_data.map)
	{
		data->map_data.map = (int **)malloc(sizeof(int *)
				* data->map_data.height);
		if (!data->map_data.map)
			return (1);
		while (i < data->map_data.height)
		{
			data->map_data.map[i] = malloc(sizeof(int) * data->map_data.width);
			if (!data->map_data.map[i])
				return (1);
			i++;
		}
	}
	if (fill_map_next(line, data) == 1)
		return (1);
	return (0);
}

static int	calcul_size_map(int fd, t_data *data)
{
	char	*line;
	int		ret;

	data->map_data.height = 0;
	data->map_data.width = 0;
	ret = get_next_line(fd, &line);
	if (ret == -1)
		return (1);
	while (ret == 1)
	{
		if (ft_strlen(line) == 0)
			continue ;
		else
		{
			data->map_data.height++;
			if (ft_strlen(line) > data->map_data.width)
				data->map_data.width = ft_strlen(line);
		}
		free(line);
		ret = get_next_line(fd, &line);
		if (ret == -1)
			return (1);
	}
	return (0);
}

int	parse_map(int fd, t_data *data)
{
	char	*line;
	int		ret;
	int		fd_tmp;

	fd_tmp = fd;
	calcul_size_map(fd_tmp, data);
	ret = get_next_line(fd, &line);
	if (ret == -1)
		return (1);
	while (ret == 1)
	{
		if (ft_strlen(line) == 0 && !data->map_data.map)
			continue ;
		else if (fill_map(line, data) == 1)
		{
			free(line);
			return (1);
		}
		free(line);
		ret = get_next_line(fd, &line);
		if (ret == -1)
			return (1);
	}
	return (0);
}
