/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_events_capture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:11:01 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/08 13:52:16 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
 *
 *	on rentre dans le bordel dur a se souvenir, on est sur des principes de vecteurs.
 *	on y modifie l'angle de vision par rapport au nouveau positionnement.
 *	i va definir si on tourne a gauche ou a droite
 *
 */

static void		cub_vision(t_pxl *p, double i)
{
	double	tmp_plane; // idem pour p->rplane.x
	double	tmp_dir; // va servir a conserver p->dir.x
	double	c;
	double	s;

	c = cos(i);
	s = sin(i);
	tmp_dir = p->dir.x;
	tmp_plane = p->rplane.x;
	p->dir.x = p->dir.x * c - p->dir.y * s;
	p->dir.y = tmp_dir * s + p->dir.y * c;
	p->rplane.x = p->rplane.x * c - p->rplane.y * s;
	p->rplane.y = tmp->plane * s + p->rplane.y * c;
}

/*
 *
 *	on va y calculer notre nouvelle position apres un mouvement / une action.
 *	puis appeller cub_vision pour adapter la vision du joueur
 *
 */

void		cub_moove(t_plx *p)
{
	double	new_posx;
	double	new_posy;

	new_posx = p->dir.x * p->speed;
	new_posy = p->dir.y * p->speed;
	if (p->up == 1)
	{
		if (!(p->map[(int)(p->pos.x + new_posx)][(int)p->pos.y]))
			p->pos.x += new_posx;
		if (!(p->map[(int)p->pos.x][(int)(p->pos.y - new_posy)]))
			p->pos.y += new_posy;
	}
	if (p->left == 1)
		cub_vision(p, 0.1);
	if (p->right == 1)
		cub_vision(p, -0.1);
	if (p->down == 1)
	{
		if (!(p->map[(int)(p->pos.x - new_posx)][(int)(p->pos.y)]))
			p->pos.x -= new_posx;
		if (!(p->map[(int)(p->pos.x)][(int)(p->pos.y - new_posy)]))
			p->pos.y -= new_posy;
	}
}

/*
 * 							Les Keycodes :
 *	126 = Aup		125 = Adown		124 = Aleft		123 = Aright
 *	 13 = W		  	  2 = S		  	  1 = A			  0 = D
 *	 78 = ?		 	 69 = ?		 	 82 = ?		 	 29 = ?
 *	 53 = ?		 	 18 = ?		 	 19 = ?		 	 20 = ?
 */

/*
 *	Key Release va terminer une action a la liberation de la touche 
 *	pressee. cela va nous permettre de creer du momentum de
 *	mouvement.
 */

int		cub_key_release(int keycode, t_pxl *p)
{
	if (keycode == 126 || keycode == 13)
		p->up = 0;
	if (keycode == 125 || keycode == 1)
		p->down = 0;
	if (keycode == 123 || keycode == 0)
		p->left = 0;
	if (keycode == 124 || keycode == 2)
		p->right = 0;
	return (0);
}

/*
 *	Key Press va activez une action des qu'une touche est pressee.
 */

int		cub_key_press(int keycode, t_pxl *p)
{
	if (!p->check && (keycode == 18 || keycode == 19))
		keycode == 18 ? cub_parsing(p, MAP1) : cub_parsing(p, MAP2);
	if (!p->check && keycode == 20)
		cub_parsing(p, MAP3);
	if (keycode == 126 || keycode == 13)
		p->up = 1;
	if (keycode == 125 || keycode == 1)
		p->down = 1;
	if (keycode == 123 || keycode == 0)
		p->left = 1;
	if (keycode == 124 || keycode == 2)
		p->right = 1;
	if ((keycode == 78 && p->speed > 0.02)
			|| (keycode == 69 && p->speed < 0.3))
		p->speed += (keycode == 69 ? 0.01 : -0.01);
	if (keycode == 82 || keycode == 29)
		cub_setup(p);
	if (keycode == 53)
		exit(1); // faut changer ca.
}
