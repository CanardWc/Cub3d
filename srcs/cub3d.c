/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:40:52 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/10 18:13:41 by fgrea            ###   ########lyon.fr   */
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
 *   le texte est adapte a la taille de la fenetre.
 *   i est la pour la couleur.
 */

static void	cub_begin(t_data d)
{
	int	x;
	int	y;
	int	i;

	x = RESX / 2;
	y = RESY / 2;
	i = 0x00FF00;
	mlx_string_put(d.mlx, d.win, x - 30, y - 15, i, "cub3d");
	mlx_string_put(d.mlx, d.win, x - 50, y + 15, i, "Maps: 1/2/3");
}

/*
 *
 *	La on va devoir passer a argc + argv, pour que les gens puissent inserer
 *	leurs propres maps.
 *	mlx_init intialise la librarie et la link au pointeur mlx;
 *	mlx_new_window cree la fenetre;
 *	mlx_new_image cree l'image qu'on va plus tard deposer dans la fenetre;
 *	mlx_get_data_addr nous procure toutes les donnees pour nous aider a traiter
 *	correctement l'image;
 *	mlx_hook va nous permettre de reperer des evenements (touche clavier)
 *	mlx_loop va nous permettre d'activer notre boucle de controle;
 *
 */

int		main(void)
{
	t_data	d;

	d.check = 0; // un trigger pour savoir si la map est bien parsee, pas tres joli ca.
	d.mlx = mlx_init();
	d.win = mlx_new_window(d.mlx, RESX, RESY, "cub3");
	d.img.im = mlx_new_image(d.mlx, RESX, RESY);
	d.img.imc = mlx_get_data_addr(d.img.im, &d.img.bpp, &d.img.imlen, \
			&d.img.endi);
	cub_begin(d);
	cub_setup(&d); // dans cub_thread_set, pas ouf et un peux con.
	mlx_hook(d.win, 2, 1L << 0, cub_key_press, &d);
	mlx_hook(d.win, 3, 1L << 1, cub_key_release, &d);
	mlx_hook(d.win, 17, 1L << 15, cub_key_quit, NULL); // reaction au quit, a revoir?
	mlx_loop_hook(d.mlx, cub_logic, &d);
	mlx_loop(d.mlx);
	// une fonction de free au cas ou?
	return (0);
}
