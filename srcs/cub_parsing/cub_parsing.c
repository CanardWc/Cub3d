/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:51:38 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/10 17:52:00 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void		ft_strdel(char **s)
{
	free(*s);
	*s = NULL;
}

static void		cub_freestr2d(t_data *p)
{
	int			i;

	i = 0;
	while (p->line[i])
	{
		ft_strdel(&(p->line[i]));
		++i;
	}
	ft_strdel(&(p->line[i]));
	free(p->line);
}

static int		cub_split_line(t_data *p)
{
	char		*line;
	int			ret;

	ret = 0;
	if (get_next_line(p->fd, &line) == 1)
	{
		p->line = ft_split(line, ' ');
		free(line);
		++ret;
	}
	else
		free(line);
	return (ret);
}

static void		cub_int2d(t_data *p, char *file)
{
	char		*line;
	int			len;

	p->cmap.x = 0;
	p->cmap.y = 0;
	while (get_next_line(p->fd, &line) == 1)
	{
		++p->cmap.y;
		len = ft_strlen(line);
		free(line);
	}
	free(line);
	if (p->cmap.y == 0 || len == 0)
		cub_error("read has failed");
	p->map = (int **)malloc(sizeof(int *) * p->cmap.y);
	close(p->fd);
	p->fd = open(file, O_RDONLY);
	cub_split_line(p);
	while (p->line[p->cmap.x])
		++p->cmap.x;
	while (p->cmap.y > 0)
	{
		p->map[p->cmap.y - 1] = (int*)malloc(sizeof(int) * p->cmap.x);
		--p->cmap.y;
	}
}

void			cub_parsing(t_data *p, char *file)
{
	int			map_x;

	map_x = 0;
	if ((p->fd = open(file, O_RDONLY)) <= 0)
		cub_error("open has failed");
	cub_int2d(p, file);
	while (map_x < p->cmap.x)
	{
		p->map[0][map_x] = ft_atoi(p->line[map_x]);
		++map_x;
	}
	cub_freestr2d(p);
	while (cub_split_line(p) == 1)
	{
		++p->cmap.y;
		map_x = -1;
		while (p->line[++map_x])
			p->map[p->cmap.y][map_x] = ft_atoi(p->line[map_x]);
		cub_freestr2d(p);
		if (map_x != p->cmap.x)
			cub_error("invalid map");
	}
	++p->cmap.y;
	p->check = 1;
}
