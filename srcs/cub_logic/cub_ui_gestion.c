/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_ui_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:18:26 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/17 13:56:05 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
 * 	placement de l'hud de jeu
 * 	i est la couleur affichee
 */

void		cub_hud(t_data d)
{
	int	x;
	int	y;
	int	i;

	x = 20;
	y = 600;
	i = 0x00FF00;
	mlx_string_put(d.mlx, d.win, x, y + 32, i, "Moove : wasd / Arrows");
	mlx_string_put(d.mlx, d.win, x, y + 48, i, "Speed :    + / -     ");
	mlx_string_put(d.mlx, d.win, x, y + 64, i, "Reset :      0       ");
	mlx_string_put(d.mlx, d.win, x, y + 80, i, "Quit  :     esc      ");
}

/*
 *	Remplissage de l'image pour la minimap
 */

static void	cub_put_map_to_img(t_data *d, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i <= 5)
	{
		j = -1;
		while (++j <= 5)
			cub_put_pixel(d, x + i, y + j, color);
	}
}

/*
 *	Preparation a la mise en place de la minimap
 */

void		cub_put_map(t_data *d)
{
	int	i;
	int	j;

	if (d->cmap.x * 5 > RESX / 2 || d->cmap.y * 5 > RESY / 2)
		return ;
	i = -1;
	while (++i < d->cmap.x)
	{
		j = -1;
		while (++j < d->cmap.y)
		{
			if (d->map[j][i] == 1)
				cub_put_map_to_img(d, i + (5 * (i + 1)), j + (5 * (j + 1)), \
						0x00FF00);
			else if ((int)d->pos.x == j && (int)d->pos.y == i)
				cub_put_map_to_img(d, i + (5 * (i + 1)), j + (5 * (j + 1)), \
						0x000000);
			else
				cub_put_map_to_img(d, i + (5 * (i + 1)), j + (5 * (j + 1)), \
						0xFFFFFF);
		}
	}
}
