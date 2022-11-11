/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_events_capture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:11:01 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/11 10:22:07 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

int		cub_key_release(int keycode, t_data *d)
{
	if (keycode == 126 || keycode == 13)
		d->up = 0;
	if (keycode == 125 || keycode == 1)
		d->down = 0;
	if (keycode == 123 || keycode == 0)
		d->left = 0;
	if (keycode == 124 || keycode == 2)
		d->right = 0;
	return (0);
}

/*
 *	Key Press va activez une action des qu'une touche est pressee.
 */

int		cub_key_press(int keycode, t_data *d)
{
	if (!d->check && (keycode == 18 || keycode == 19))
		keycode == 18 ? cub_parsing(d, MAP1) : cub_parsing(d, MAP2);
	if (!d->check && keycode == 20)
		cub_parsing(d, MAP3);
	if (keycode == 126 || keycode == 13)
		d->up = 1;
	if (keycode == 125 || keycode == 1)
		d->down = 1;
	if (keycode == 123 || keycode == 0)
		d->left = 1;
	if (keycode == 124 || keycode == 2)
		d->right = 1;
	if ((keycode == 78 && d->speed > 0.02)
			|| (keycode == 69 && d->speed < 0.3))
		d->speed += (keycode == 69 ? 0.01 : -0.01);
	if (keycode == 82 || keycode == 29)
		cub_setup(d);
	if (keycode == 53)
		exit(1); // faut changer ca.
	return (0);
}
