/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbounor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:03:52 by Leo               #+#    #+#             */
/*   Updated: 2022/11/10 14:00:37 by lbounor          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	fill_texture_xpm(char *line, t_data *data, int *i)
{
	char	**new_line;

	new_line = ft_split(line, ' ');
	if (!new_line)
		return (1);
	if (ft_strncmp(new_line[0], "NO", 3) == 0
		|| ft_strncmp(new_line[0], "SO", 3) == 0
		|| ft_strncmp(new_line[0], "WE", 3) == 0
		|| ft_strncmp(new_line[0], "EA", 3) == 0)
	{
		if (ft_strncmp(new_line[0], "NO", 3) == 0)
			data->map_data.xpm[0] = new_line[1];
		if (ft_strncmp(new_line[0], "NO", 3) == 0)
			data->map_data.xpm[1] = new_line[1];
		if (ft_strncmp(new_line[0], "NO", 3) == 0)
			data->map_data.xpm[2] = new_line[1];
		if (ft_strncmp(new_line[0], "NO", 3) == 0)
			data->map_data.xpm[3] = new_line[1];
		i++;
	}
	ft_free_char(new_line);
	return (0);
}

static int	fill_texture_rgb(char *line, t_data *data, int *i)
{
	char	**new_line;

	new_line = ft_split(line, ' ');
	if (!new_line)
		return (1);
	if (ft_strncmp(new_line[0], "F", 1) == 0
		|| ft_strncmp(new_line[0], "C", 1) == 0)
	{
		if (ft_strncmp(new_line[0], "F", 1) == 0)
			data->map_data.rgb[0] = new_line[1];
		if (ft_strncmp(new_line[0], "C", 1) == 0)
			data->map_data.rgb[1] = new_line[1];
		i++;
	}
	ft_free_char(new_line);
	return (0);
}

static int	malloc_texture(t_data *data)
{
	data->map_data.xpm = malloc(sizeof(char *) * 5);
	if (!data->map_data.xpm)
		return (1);
	data->map_data.rgb = malloc(sizeof(char *) * 3);
	if (!data->map_data.rgb)
		return (1);
	return (0);
}

int	parse_texture(int fd, t_data *data)
{
	char	*line;
	int		ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (malloc_texture(data) == 1)
		return (1);
	while (data->map_data.xpm[i] < 4 || data->map_data.rgb[j] < 2)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			return (1);
		if (ft_strlen(line) == 0)
			continue ;
		else if (fill_texture_xpm(line, data, &i) == 1
			|| fill_texture_rgb(line, data, &j) == 1)
		{
			free(line);
			return (1);
		}
		free(line);
		if (ret == 0)
			break ;
	}
	return (0);
}
