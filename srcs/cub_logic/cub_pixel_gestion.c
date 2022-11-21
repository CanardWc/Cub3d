/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_pixel_gestion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:39:30 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/21 17:00:07 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
 *	Fonction simple qui place un pixel de facon safe au bon emplacement et a
 *	la bonne couleur;
 */

void	cub_put_pixel(t_data *d, int x, int y, int color)
{
	int	*tmp;

	if (y >= RESY || x >= RESX || x < 0 || y < 0)
		return ;
	tmp = (int *)&d->img.imc[(y * d->img.imlen) + (x * (d->img.bpp / 8))];
	*tmp = color;
}

/*
 *	cub_find_texture_color will search on the right texture which color
 *		will fit the pixel;
 */

/*
static void	cub_find_texture_color(t_data *d, int x, t_img texture)
{
	double wall_x;
	int	tex_x;
	int	tex_y;
	double	step;
	double	texpos;
	int	color;
	int	y;

	if (d->wall == 0)
		wall_x = d->r.pos.y - d->pw_dist * d->r.disd.y;
	else
		wall_x = d->r.pos.x - d->pw_dist * d->r.disd.x;
	wall_x -= (int)wall_x;
	tex_x = (int)(wall_x * texture.img_w);
	if (d->wall == 0)
		tex_x += texture.img_w;
	else if (d->wall == 1)
		tex_x += texture.img_w - 1;
	step = 1 * texture.img_w / d->rh;
	texpos = (d->wstart - RESY / 2 + d->rh / 2) * step - 1;
	y = d->wstart;
	while (y < d->wend)
	{
		tex_y = (int)texpos & (texture.img_h - 1);
		texpos += step;
		color = ((int *)texture.imc)[texture.img_w * tex_y + tex_x];
		cub_put_pixel(d, x, y, color);
		y++;
	}
}*/

static void	cub_find_texture_color(t_data *d, int x, t_img texture)
{
	double	wall_x;
	int tex_x;
	int	tex_y;
	double	step;
	double	texpos;
	unsigned int	color;
	int	y;

	if (d->wall == 0)
		wall_x = d->r.pos.y + d->pw_dist * d->r.disd.y;
	else
		wall_x = d->r.pos.x + d->pw_dist * d->r.disd.x;
	wall_x -= floor(wall_x);
	//ft_printf("wall_x = [%d]\n", wall_x);
	tex_x = (int)(wall_x * (double)(texture.img_w));
	if (d->wall == 0 && d->r.disd.x > 0)
		tex_x = texture.img_w - tex_x - 1;
	if (d->wall == 1 && d->r.disd.y < 0)
		tex_x = texture.img_w - tex_x - 1;
	step = 1.0 * texture.img_h / d->rh;
	texpos = (d->wstart - RESY / 2 + d->rh / 2) * step;
	y = d->wstart;
	ft_printf("tex_x = [%d] wall_x = [%d] d->r.pos.x = [%f] d->pw_dist = [%f], d->r.disd.x = [%f]\n", tex_x, wall_x, d->r.pos.x, d->pw_dist, d->r.disd.x);
	while (y < d->wend)
	{
	//	ft_printf("tex_y = [%d]\n", tex_y);
	//	int lol = 20;
	//	wait(&lol);
		tex_y = (int)texpos & (texture.img_h - 1);
		texpos += step;
		int *test = (int *)&texture.imc[(tex_y) * texture.imlen + tex_x * (texture.bpp / 8)];
		color = *test;
		cub_put_pixel(d, x, y++, color);
	}
	//ft_printf("y end = [%d]\n", y);
}

/*
 *	Remplit une colonne entiere, interressant vu que les lignes les plus
 *	longues sont deja dessinees;
 */

void		cub_fill_columns(t_data *d, int x, t_img texture)
{
	int	y;

	y = 0;
	d->ceil_color = 0xC00000A0; // A CHANGER UNE FOIS LE PARSING;
	d->floor_color = 0xA0A0A0; // A CHANGER UNE FOIS LE PARSING;
	while (y < d->wstart)  // plafond
		cub_put_pixel(d, x, y++, d->ceil_color);
/*	while (y >= d->wstart && y <= d->wend) // murs
	{
		//des trucs
	}
	ft_printf("coucou\n");*/
	cub_find_texture_color(d, x, texture);
	y = d->wend;
	//while (y >= d->wstart && y <= d->wend) // murs
	//	cub_put_pixel(d, x, y++, d->color);
	while (y < RESY)
		cub_put_pixel(d, x, y++, d->floor_color); // sols
	ft_printf("x = [%d]\n", x);
}
