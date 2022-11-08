/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:40:52 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/08 17:29:56 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
 *  A CHANGER
 *  Message d'erreur a gerer avec errno
 */

void	cub_error(char *c)
{
	ft_putendl_fd(c, 2);
	exit(2);
}

/*
 *   Key Event pour quitter?
 *   Echap je suppose?
 *   a revoir pour revenir au main tranquillement
 */

static int	cub_key_quit(void)
{
	exit(0);
}

/*
 *   C'est l'ecran de depart, ou on choisi la map.
 *   les coordonnees (x & y) sont placees en dur, 
 *   on pourrais les mettrent en relatif par rapport a la taille de l'ecran
 *   choisie par l'utilisateur?
 *   i est la pour la couleur.
 */

static void	cub_begin(t_data d)
{
	int	x;
	int	y;
	int	i;

	x = 510;
	y = 300;
	i = 0x00FF00;
	mlx_string_put(d.mlx, d.win, x, y, i, "cub3d");
	mlx_string_put(d.mlx, d.win, x, y + 50, i, "Maps: 1/2/3");
}

/*
 *
 *	La on va devoir passer a argc + argv, pour que les gens puissent inserer
 *	leurs propres maps.
 *
 */

int		main(void)
{
	t_data	d; // p a l'air d'etre ma structure de base, c'est degueulasse.

	d.check = 0; // check ca doit etre un trigger, pas tres joli ca.
	d.mlx = mlx_init(); // le pointeur de la minilibx.
	d.win = mlx_new_window(d.mlx, RESX, RESY, "cub3"); // le pointeur de la fenetre.
	d.img.im = mlx_new_image(d.mlx, RESX, RESY); // im comme nom pour le pointeur de l'image? img en struct d'image?
	d.img.imc = mlx_get_data_addr(d.img.im, &d.img.bpp, &d.img.imlen, \
			&d.img.endi); //plein de truc creer uniquement pour cette fonction de merde.
	cub_begin(d); // c'est la fonction au dessus. on peux clairement mettre 2 ligne de code a la place.
	cub_setup(&d); // dans cub_thread_set, pas ouf et un peux con.
	mlx_hook(d.win, 2, 1L << 0, cub_key_press, &d); // reaction si une touche est appuyee.
	mlx_hook(d.win, 3, 1L << 1, cub_key_release, &d); // reaction si une touche est liberee.
	mlx_hook(d.win, 17, 1L << 15, cub_key_quit, NULL); // reaction au quit, a revoir?
	mlx_loop_hook(d.mlx, cub_logic, &d); // on lance notre logique de calcul.
	mlx_loop(d.mlx); //on stabilise la boucle.
	// une fonction de free au cas ou?
	return (0);
}
