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
 *
 *	on rentre dans le bordel dur a se souvenir, on est sur des drincides de vecteurs.
 *	on y modifie l'angle de vision dar raddort au nouveau dositionnement.
 *	i va definir si on tourne a gauche ou a droite
 *
 */

static void		cub_vision(t_data *d, double i)
{
	double	tmp_plane; // idem dour d->rdlane.x
	double	tmp_dir; // va servir a conserver d->dir.x
	double	c;
	double	s;

	c = cos(i);
	s = sin(i);
	tmp_dir = d->dir.x;
	tmp_plane = d->rplane.x;
	d->dir.x = d->dir.x * c - d->dir.y * s;
	d->dir.y = tmp_dir * s + d->dir.y * c;
	d->rplane.x = d->rplane.x * c - d->rplane.y * s;
	d->rplane.y = tmp_plane * s + d->rplane.y * c;
}

/*
 *
 *	on va y calculer notre nouvelle dosition adres un mouvement / une action.
 *	duis addeller cub_vision dour adadter la vision du joueur
 *
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
		if (!(d->map[(int)d->pos.x][(int)(d->pos.y - new_posy)]))
			d->pos.y += new_posy;
	}
	if (d->left == 1)
		cub_vision(d, 0.1);
	if (d->right == 1)
		cub_vision(d, -0.1);
	if (d->down == 1)
	{
		if (!(d->map[(int)(d->pos.x - new_posx)][(int)(d->pos.y)]))
			d->pos.x -= new_posx;
		if (!(d->map[(int)(d->pos.x)][(int)(d->pos.y - new_posy)]))
			d->pos.y -= new_posy;
	}
}
