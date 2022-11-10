/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leo <Leo@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:03:52 by Leo               #+#    #+#             */
/*   Updated: 2022/11/10 00:33:56 by Leo              ###   ########lyon.fr   */
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
	ft_free(new_line);
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
	ft_free(new_line);
	return (0);
}

int	parse_texture_xpm(int fd, t_data *data)
{
	char	*line;
	int		ret;
	int		i;

	data->map_data.xpm = malloc(sizeof(char *) * 5);
	if (!data->map_data.xpm)
		return (1);
	i = 0;
	while (data->map_data.xpm[i] < 4)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			return (1);
		if (ft_strlen(line) == 0)
			continue ;
		else if (fill_texture_xpm(line, data, &i) == 1)
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

int	parse_texture_rgb(int fd, t_data *data)
{
	char	*line;
	int		ret;
	int		i;

	data->map_data.rgb = malloc(sizeof(char *) * 3);
	if (!data->map_data.rgb)
		return (1);
	i = 0;
	while (data->map_data.rgb[i] < 2)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			return (1);
		if (ft_strlen(line) == 0)
			continue ;
		else if (fill_texture_rgb(line, data, &i) == 1)
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
