/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:41:32 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/11 20:42:59 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define RESX 1280
# define RESY 720

# define MAP1 "ressources/maps/map01"
# define MAP2 "ressources/maps/map02"
# define MAP3 "ressources/maps/map03"
# define SKY "ressources/textures/skybox/sky.xpm"

# define TMP_NO "ressources/textures/walls/Sr1.xpm"
# define TMP_SO "ressources/textures/walls/White4.xpm"
# define TMP_WE "ressources/textures/walls/Wall2.xpm"
# define TMP_EA "ressources/textures/walls/Wall1.xpm"

# define NORTH 1
# define SOUTH 2
# define WEST 3
# define EAST 4

# include <libft.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>

/*
 *	structure pour retenir l'axe X et Y en Int;
 */

typedef struct		s_ixy
{
	int				x;
	int				y;
}					t_ixy;

/*
 *	structure pour retenir l'axe X et Y en Double;
 */

typedef struct		s_dxy
{
	double			x;
	double			y;
}					t_dxy;

/*
 *	Coordonnees de la map et du parsing;
 */

typedef struct		s_map
{
	int				x;
	int				y;
	int				**map;
}					t_map;

/*
 *	informations sur l'image;
 *	permet de facilement s'oriente grace a:
 *	imlen (pour l'axe y);
 *	bpp (pour l'axe x);
 */

typedef struct		s_img
{
	void			*im;
	char			*imc;
	int				imlen;
	int				bpp;
	int				endi;
}					t_img;

/*
 *	Structure pour le calcul des rayons;
 */

typedef struct		s_ray
{
	double			cam;
	t_dxy			pos;
	t_dxy			dir;
	t_dxy			dist;
	t_dxy			disd;
}					t_ray;

/*
 *	Macro structure qui comptiens toutes les informations
 *	majeures;
 */

typedef struct		s_data
{
	char			*choice;	//
	int				fd;			//	tout ca la
	char			**line;		//	faut qu'on le vire
	t_ixy			cmap;		//	ca sert a rien
	int				**map;		//	ya pas besoin de ca
	int				check;		//

	void			*mlx;
	void			*win;
	int				color;

	t_img			img;
	t_img			sky;

	int				ceil_color;
	int				floor_color;
	t_img			w_no;
	t_img			w_so;
	t_img			w_we;
	t_img			w_ea;

	t_ray			r;
	int				wall;
	int				hit;
	t_dxy			pos;
	t_dxy			dir;
	t_dxy			rplane;
	t_ixy			rmap;
	t_ixy			step;
	double			pw_dist;				

	int				wstart;
	int				wend;
	int				rh;

	double			speed;
	int				up;
	int				down;
	int				left;
	int				right;
}					t_data;

void				cub_parsing(t_data *d, char *line);

int					cub_key_press(int keycode, t_data *d);
int					cub_key_release(int keycode, t_data *d);

void				cub_put_pixel(t_data *d, int x, int y, int color);
int					cub_logic(t_data *d);
void				cub_fill_columns(t_data *d, int x, t_img texture);
void				cub_ray_logic(t_data *d);
void				cub_moove(t_data *d);
void				cub_setup(t_data *d);
void				cub_put_map(t_data *d);
void				cub_error(char *c);

void				cub_hud(t_data d);
void				cub_put_map(t_data *d);

#endif
