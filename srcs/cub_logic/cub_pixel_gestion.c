/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_pixel_gestion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:39:30 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/08 17:36:03 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
 *	Fonction simple qui place un pixel de facon safe au bon emplacement et a
 *	la bonne couleur;
 */

void	cub_put_pixel(t_data *d, int x, int y, int color)
{
	int	*tmp;

	if (y >= RESY || x >= RESX || x < 0 || y < 0)
		return ;
	tmp = (int *)&d->img.imc[(y * d->img.imlen) + (x * (d->img.bpp / 8))];
	*tmp = color;
}

/*
 *	Remplit une colonne entiere, interressant vu que les lignes les plus
 *	longues sont deja dessinees;
 */

void		cub_fill_columns(t_data *d, int x)
{
	int	y;

	y = 0;
	while (y < d->wstart)
		cub_put_pixel(d, x, y++, 0xC00000A0);
	while (y >= d->wstart && y <= d->wend)
		cub_put_pixel(d, x, y++, d->color);
	while (y < RESY)
		cub_put_pixel(d, x, y++, 0xA0A0A0);
}
