/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_thread_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:25:52 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/08 12:10:52 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
 * 	ici on setup les valeurs de p, et on place la skybox sur l'image.
 */

void	cub_setup(t_pxl *p)
{
	// ces deux valeurs servent de futur adresses pour mlx_xpm_
	int	win_x; // resolution en largeur.
	int	win_y; // resolution en hauteur.
	p->pos.x = 1.501; // data referent a quoi?
	p->pos.y = 1.501; // idem, position?
	p->dir.x = 1; // direction?
	p->dir.y = 0;
	p->rplane.x = 0; // un plan?
	p->rplane.y = -0.80; // on dirais un point de vue.
	p->speed = 0.1; // ca c'est pour la vitesse de deplacement de base.
	p->sky.im = mlx_xpm_file_to_image(p->mlx, SKY, &win_x, &win_y); // on place la sky box en memoire image;
	p->sky.imc = mlx_get_data_addr(p->sky.im, &p->sky.bpp, &p->sky.imlen, \
			&p->sky.endi); // on transforme la memoire image pour qu'elle soit lue correctement par la fonction mlx.
}

/*
 *
 * 	la on place l'hud de jeu
 * 	rien de special, on pourrais enlever les x et y et les remplacers par un calcul
 * 	relatif a la resolution de l'ecran
 *
 */

static void		cub_hud(t_pxl p)
{
	int	x;
	int	y;
	int	i;

	x = 20; // largeur
	y = 600; // hauteur
	i = 0x00FF00; // couleur;
	mlx_string_put(p.mlx, p.win, x, y + 32, i, "Moove : wasd / Arrows");
	mlx_string_put(p.mlx, p.win, x, y + 48, i, "Speed :    + / -     ");
	mlx_string_put(p.mlx, p.win, x, y + 64, i, "Reset :      0       ");
	mlx_string_put(p.mlx, p.win, x, y + 80, i, "Quit  :     esc      ");
}

/*
 *
 * c'est le main de notre logique de calcul;
 *
 */

int		cub_launcher(t_pxl *p)
{
	if (p->check == 0) // verificateur, on dirais qu'il verifie si la map est bien parsee?
		return (0);    // on peux vraiment faire sans je pense.
	cub_moove(p); // events_capture, on y defini les nouvelles positions.
	cub_ray_study(p); // collision detector, visiblement on calcul ou les rayobs vont taper. 
	cub_put_map(p); // pixel_gestion, on y rempli l'image apres avoir calculer les rayons.
	mlx_clear_window(p->mlx, p->win); // on suprime l'image dans la fenetre;
	mlx_put_image_to_window(p->mlx, p->win, p->sky.im, 0, 0); // on place l'image sky box dans la fenetre;
	mlx_put_image_to_window(p->mlx, p->win, p->sky.im, 0, 0); // on place l'image de l'environnement dans la fenetre;
	cub_hud(*p); // on place les lignes de texte qui compose l'hud;
	return (0);
}
