/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leo <Leo@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:41:32 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/10 01:55:34 by Leo              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define RESX 1280
# define RESY 720

# define MAP1 "maps/map01"
# define MAP2 "maps/map02"
# define MAP3 "maps/map03"
# define SKY "textures/sky.xpm"

# include <libft.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include <unistd.h>

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
	int				**map; //map final, contient des entiers
	char			**xpm;
	char			**rgb;
	int				width;
	int				height;
}					t_map;

/*
 *	informations sur les textures ;
 */
typedef struct s_texture
{
	void	*img;
	int		bits_per_pixel;
	int		endian;
	char	*texture_path;
	int		width;
	int		height;
	int		line_length;
	void	*text_address;
}	t_texture;
/*
 *	informations sur l'image;
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

	t_map			map_data;
	void			*mlx;
	void			*win;
	int				color;

	t_img			img;
	t_img			sky;

	t_ray			r;
	int				wall;
	int				hit;
	t_dxy			pos;
	t_dxy			dir;
	t_dxy			rplane;
	t_ixy			rmap;
	t_ixy			step;

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
void				cub_fill_columns(t_data *d, int x);
void				cub_ray_logic(t_data *d);
void				cub_moove(t_data *d);
void				cub_setup(t_data *d);
void				cub_put_map(t_data *d);
void				cub_error(char *c);

void				cub_hud(t_data d);
void				cub_put_map(t_data *d);

#endif
