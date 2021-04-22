/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:17:15 by fgrea             #+#    #+#             */
/*   Updated: 2021/04/22 18:02:42 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


typedef	struct	s_data
{
	int			res_x;
	int			res_y;

	int 		roof_color;
	int			floor_color;

	char		*textures[10];
}				t_data;

typedef struct	s_treat
{
	char		*format;
	void		(*fct)(t_data *, char *);
}				t_treat;

const	t_treat	treat_fct[] = {
	{ "R", &ft_treat_r }, { "NO", &ft_treat_no },
	{ "SO", &ft_treat_so }, { "WE", &ft_treat_we },
	{ "EA", &ft_treat_ea }, { "S", &ft_treat_s },
	{ "F", &ft_treat_f }, { "C", &ft_treat_c } };

void	ft_treat_r(t_data *data, char *line);
void	ft_treat_no(t_data *data, char *line);
void	ft_treat_so(t_data *data, char *line);
void	ft_treat_we(t_data *data, char *line);
void	ft_treat_ea(t_data *data, char *line);
void	ft_treat_s(t_data *data, char *line);
void	ft_treat_f(t_data *data, char *line);
void	ft_treat_c(t_data *data, char *line);

void	ft_treat_map(t_data *data, char *line);

int		error_gestion(int type);
{
	ft_putstr_fd("Error\n", 1);
	if (type == 0)
		ft_putstr_fd("The file is not a .cub file.\n", 1);
	if (type == 1)
		ft_putstr_fd("the .cub file can't be opened.\n", 1);
	if (type == 2)
		ft_putstr_fd("An error happened while reading the .cub file.\n", 1);
	if (type == 3)
		ft_putstr_fd("the .cub file have a wrong format.\n", 1);
	exit(0);
}

void	set_data(int fd, char ***data)
{
	int	read_count;
	char	*line;

	read_count = 1;
	while (read_count)
	{
		read_count = 
	}
}

void	set_map(int	fd, char ***map)
{
	
}

int		main(int ac, char **av)
{
	int	fd;
	int	read_count;
	t_data	data;
	char	**map;

	if (ft_strcmp(av[1] + (ft_strlen(av[1] - 4)), ".cub"))
		error_gestion(0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error_gestion(1);
	set_data(fd, &data);
	set_map(fd, &map;
	close(fd);
	return (0);
}
