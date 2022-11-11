/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_logic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:09:45 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/11 20:45:53 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
 *	cub_setup_textures setup les textures avec mlx_xpm_file_to_image puis
 *		mlx_get_data_addr afin de pouvoir traiter rapidement les calculs
 */

void	cub_setup_textures(t_data *d)
{
	// ces deux valeurs servent de futur adresses pour mlx_xpm_
	int	win_x; // resolution en largeur.
	int	win_y; // resolution en hauteur.

	win_x = RESX;
	win_y = RESY;
	d->w_no.im = mlx_xpm_file_to_image(d->mlx, TMP_NO, &win_x, &win_y);
	d->w_no.imc = mlx_get_data_addr(d->w_no.im, &d->w_no.bpp, &d->w_no.imlen, \
			&d->w_no.endi);
	d->w_so.im = mlx_xpm_file_to_image(d->mlx, TMP_SO, &win_x, &win_y);
	d->w_so.imc = mlx_get_data_addr(d->w_so.im, &d->w_so.bpp, &d->w_so.imlen, \
			&d->w_so.endi);
	d->w_we.im = mlx_xpm_file_to_image(d->mlx, TMP_WE, &win_x, &win_y);
	d->w_we.imc = mlx_get_data_addr(d->w_we.im, &d->w_we.bpp, &d->w_we.imlen, \
			&d->w_we.endi);
	d->w_ea.im = mlx_xpm_file_to_image(d->mlx, TMP_EA, &win_x, &win_y);
	d->w_ea.imc = mlx_get_data_addr(d->w_ea.im, &d->w_ea.bpp, &d->w_ea.imlen, \
			&d->w_ea.endi);
	d->sky.im = mlx_xpm_file_to_image(d->mlx, SKY, &win_x, &win_y);
	d->sky.imc = mlx_get_data_addr(d->sky.im, &d->sky.bpp, &d->sky.imlen, \
			&d->sky.endi);
}

/*
 * 	ici on setup les valeurs de p, et on place la skybox sur l'image.
 */

void	cub_setup(t_data *d)
{
	d->pos.x = 1.501; // data referent a quoi?
	d->pos.y = 1.501; // idem, position?
	d->dir.x = 1; // direction?
	d->dir.y = 0;
	d->rplane.x = 0; // un plan?
	d->rplane.y = -0.80; // on dirais un point de vue.
	d->speed = 0.1; // ca c'est pour la vitesse de deplacement de base.
	cub_setup_textures(d);
}

/*
 * 	c'est le main de notre logique de calcul;
 * 	cub_moove re-calcule les valeurs de positions apres un event;
 * 	cub_ray_logic gere la gestion de rayon, qui permet de calculer 
 * 		les distances afin d'afficher les murs;
 *	cub_put_map va remplir l'image avec les bonnes donnees;
 *	mlx_clear_window efface l'image en place dans la fenetre;
 *	mlx_put_image_to_window va placer l'image correspondante dans 
 *		la fenetre;
 *	sky represente le ciel;
 *	img est l'image precalculee;
 */

int		cub_logic(t_data *d)
{
	if (d->check == 0) // verificateur, il verifie si la map est bien parsee
		return (0);    // on peux vraiment faire sans je pense.
	cub_moove(d); // events_capture, on y defini les nouvelles positions.
	cub_ray_logic(d); // collision detector, visiblement on calcul ou les rayons vont taper. 
	cub_put_map(d); // pixel_gestion, on y rempli l'image apres avoir calculer les rayons.
	mlx_clear_window(d->mlx, d->win); // on suprime l'image dans la fenetre;
	mlx_put_image_to_window(d->mlx, d->win, d->sky.im, 0, 0); // on place l'image sky box dans la fenetre;
	ft_printf("la?\n");
	mlx_put_image_to_window(d->mlx, d->win, d->img.im, 0, 0); // on place l'image de l'environnement dans la fenetre;
	ft_printf("non?\n");
	cub_hud(*d); // on place les lignes de texte qui compose l'hud;
	return (0);
}
