/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_logic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:09:45 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/08 17:24:57 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
 * 	ici on setup les valeurs de p, et on place la skybox sur l'image.
 */

void	cub_setup(t_data *d)
{
	// ces deux valeurs servent de futur adresses pour mlx_xpm_
	int	win_x; // resolution en largeur.
	int	win_y; // resolution en hauteur.
	d->pos.x = 1.501; // data referent a quoi?
	d->pos.y = 1.501; // idem, position?
	d->dir.x = 1; // direction?
	d->dir.y = 0;
	d->rplane.x = 0; // un plan?
	d->rplane.y = -0.80; // on dirais un point de vue.
	d->speed = 0.1; // ca c'est pour la vitesse de deplacement de base.
	d->sky.im = mlx_xpm_file_to_image(d->mlx, SKY, &win_x, &win_y); // on place la sky box en memoire image;
	d->sky.imc = mlx_get_data_addr(d->sky.im, &d->sky.bpp, &d->sky.imlen, \
			&d->sky.endi); // on transforme la memoire image pour qu'elle soit lue correctement par la fonction mlx.
}

/*
 *
 * c'est le main de notre logique de calcul;
 *
 */

int		cub_logic(t_data *d)
{
	if (d->check == 0) // verificateur, on dirais qu'il verifie si la map est bien parsee?
		return (0);    // on peux vraiment faire sans je pense.
	cub_moove(d); // events_capture, on y defini les nouvelles positions.
	cub_ray_logic(d); // collision detector, visiblement on calcul ou les rayons vont taper. 
	cub_put_map(d); // pixel_gestion, on y rempli l'image apres avoir calculer les rayons.
	mlx_clear_window(d->mlx, d->win); // on suprime l'image dans la fenetre;
	mlx_put_image_to_window(d->mlx, d->win, d->sky.im, 0, 0); // on place l'image sky box dans la fenetre;
	mlx_put_image_to_window(d->mlx, d->win, d->sky.im, 0, 0); // on place l'image de l'environnement dans la fenetre;
	cub_hud(*d); // on place les lignes de texte qui compose l'hud;
	return (0);
}
