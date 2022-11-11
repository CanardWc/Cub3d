/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_pixel_gestion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:39:30 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/11 20:45:55 by fgrea            ###   ########lyon.fr   */
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

static void	cub_find_texture_color(t_data *d, int x, t_img texture)
{
	int	y;
	double	wall_x;
	int tex_x;
	int	tex_y;
	double	step;
	double	texpos;
	int	color;

	y = d->wstart;
	ft_printf("1\n");
	if (d->wall == 0)
		wall_x = d->r.pos.y + d->pw_dist * d->r.disd.y;
	else
		wall_x = d->r.pos.x + d->pw_dist * d->r.disd.x;
	ft_printf("2\n");
	tex_x = (int)(wall_x * (double)(texture.bpp / 8));
	ft_printf("3\n");
	if (d->wall == 0 && d->r.disd.x > 0)
		tex_x = texture.bpp / 8 - tex_x - 1;
	ft_printf("4\n");
	if (d->wall == 0 && d->r.disd.y < 0)
		tex_x = texture.bpp / 8 - tex_x - 1;
	ft_printf("5\n");
	step = 1.0 * (texture.imlen) / d->rh;
	ft_printf("6\n");
	texpos = (d->wstart - RESY / 2 + d->rh / 2) * step;
	ft_printf("7\n");

	while (y <= d->wend)
	{
		tex_y = (int)texpos & ((texture.imlen) - 1);
		texpos += step;
		ft_printf("OUYA?\n");
		int len = ft_strlen(texture.imc);
		ft_printf("LA LEN = [%d] LA STRING = [%s]\n",len, texture.imc);
		color = ((int *)texture.imc)[(texture.imlen) * tex_y + tex_x];
		ft_printf("OUYAA?\n");
		cub_put_pixel(d, x, y++, color);
		ft_printf("OUYAAA?\n");
		y++;
	}
	ft_printf("8\n");
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
	ft_printf("coucou\n");
	cub_find_texture_color(d, x, texture);
	ft_printf("aurevoir\n");
	y = d->wend + 1;
	//while (y >= d->wstart && y <= d->wend) // murs
	//	cub_put_pixel(d, x, y++, d->color);
	while (y < RESY)
		cub_put_pixel(d, x, y++, d->floor_color); // sols
}
