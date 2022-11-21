/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_collisions_detector.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:40:19 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/21 14:49:15 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
 *	Mise en place des informations pour la structure des rayons;
 */

static void	cub_ray_setup(t_data *d, int x)
{
	d->r.cam = 2 * x / (double)(RESX) - 1;
	d->r.pos.x = d->pos.x;
	d->r.pos.y = d->pos.y;
	d->r.dir.x = d->dir.x + d->plane.x * d->r.cam;
	d->r.dir.y = d->dir.y + d->plane.y * d->r.cam;
	d->rmap.x = (int)d->r.pos.x;
	d->rmap.y = (int)d->r.pos.y;
	d->r.disd.x = sqrt(1 + (d->r.dir.y * d->r.dir.y) / \
			(d->r.dir.x * d->r.dir.x));
	d->r.disd.y = sqrt(1 + (d->r.dir.x * d->r.dir.x) / \
			(d->r.dir.y * d->r.dir.y));
	d->hit = 0;
}

/*
 *	Permet de definir la direction de lancement des rayons dans la map
 */

static void	cub_ray_parsing(t_data *d)
{
	if (d->r.dir.x < 0)
	{
		d->step.x = -1;
		d->r.dist.x = (d->r.pos.x - d->rmap.x) * d->r.disd.x;
	}
	else
	{
		d->step.x = 1;
		d->r.dist.x = (d->rmap.x + 1.0 - d->r.pos.x) * d->r.disd.x;
	}
	if (d->r.dir.y < 0)
	{
		d->step.y = -1;
		d->r.dist.y = (d->r.pos.y - d->rmap.y) * d->r.disd.y;
	}
	else
	{
		d->step.y = 1;
		d->r.dist.y = (d->rmap.y + 1.0 - d->r.pos.y) * d->r.disd.y;
	}
}

/*
 *	Permet de definir la collision d'un rayon;
 */

static void	cub_ray_hit(t_data *d)
{
	while (d->hit == 0)
	{
		if (d->r.dist.x < d->r.dist.y)
		{
			d->r.dist.x += d->r.disd.x;
			d->rmap.x += d->step.x;
			d->wall = 0;
		}
		else
		{
			d->r.dist.y += d->r.disd.y;
			d->rmap.y += d->step.y;
			d->wall = 1;
		}
		if (d->map[d->rmap.x][d->rmap.y] == 1)
			d->hit = 1;
	}
}

/*
 *	permet de definir la distance entre le joueur et un point de collision;
 */

static void cub_ray_sizing(t_data *d)
{
	if (d->wall == 0)
		d->pw_dist = fabs((d->rmap.x - d->r.pos.x \
					+ (1 - d->step.x) / 2) / d->r.dir.x);
	else
		d->pw_dist = fabs((d->rmap.y - d->r.pos.y \
					+ (1 - d->step.y) / 2) / d->r.dir.y);
	d->rh = abs((int)(RESY / d->pw_dist));
	d->wstart = (-1 * (d->rh)) / 2 + RESY / 2;
	if (d->wstart < 0)
		d->wstart = 0;
	d->wend = d->rh / 2 + RESY / 2;
	if (d->wend >= RESY)
		d->wend = RESY - 1;
}

/*
 *	Ici on rassemble toute la logique de calcul des rayons
 */

void		cub_ray_logic(t_data *d)
{
	int	x;
	
	x = 0;
	while (x <= RESX)
	{
		cub_ray_setup(d, x);
		cub_ray_parsing(d);
		cub_ray_hit(d);
		cub_ray_sizing(d);
		if (d->wall == 0)
		{
			if (d->step.x < 0)
				cub_fill_columns(d, x++, d->w_no);
			else
				cub_fill_columns(d, x++, d->w_so);
		}
		else
		{
			if (d->step.y < 0)
				cub_fill_columns(d, x++, d->w_we);
			else
				cub_fill_columns(d, x++, d->w_ea);
		}
		/*
		if (d->wall == 0) // C'EST LA LES COULEURS DES MURS DONC FAUDRA METTRE LES TEXTURES LA;
			d->c = (d->step.x < 0 ? 0x99004C : 0xFF0000); // Nord | Sud
		else
			d->color = (d->step.y < 0 ? 0x0000FF : 0xFF9933); // Ouest | Est
		cub_fill_columns(d, x++);
		*/
	}
}
