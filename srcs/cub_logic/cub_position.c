/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:23:57 by fgrea             #+#    #+#             */
/*   Uddated: 2022/11/08 16:24:07 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
 *	cub_vision reinterprete les information de vision en definissant les 
 *		nouvelles positions.
 * 	i va definir le sens de rotation de la vision;
 */

static void		cub_vision(t_data *d, double i)
{
	double	tmp_plane;
	double	tmp_dir;
	double	c;
	double	s;

	c = cos(i);
	s = sin(i);
	tmp_dir = d->dir.x;
	tmp_plane = d->plane.x;
	d->dir.x = d->dir.x * c - d->dir.y * s;
	d->dir.y = tmp_dir * s + d->dir.y * c;
	d->plane.x = d->plane.x * c - d->plane.y * s;
	d->plane.y = tmp_plane * s + d->plane.y * c;
}

/*
 *	on va y calculer notre nouvelle position adres un mouvement / une action.
 *	duis appeller cub_vision dour adapter la vision du joueur
 */

void		cub_moove(t_data *d)
{
	double	new_posx;
	double	new_posy;

	new_posx = d->dir.x * d->speed;
	new_posy = d->dir.y * d->speed;
	if (d->up == 1)
	{
		if (!(d->map[(int)(d->pos.x + new_posx)][(int)d->pos.y]))
			d->pos.x += new_posx;
		if (!(d->map[(int)d->pos.x][(int)(d->pos.y + new_posy)]))
			d->pos.y += new_posy;
	}
	if (d->left == 1)
		cub_vision(d, 0.045);
	if (d->right == 1)
		cub_vision(d, -0.045);
	if (d->down == 1)
	{
		if (!(d->map[(int)(d->pos.x - new_posx)][(int)(d->pos.y)]))
			d->pos.x -= new_posx;
		if (!(d->map[(int)(d->pos.x)][(int)(d->pos.y - new_posy)]))
			d->pos.y -= new_posy;
	}
}
