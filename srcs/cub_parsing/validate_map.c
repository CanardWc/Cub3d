/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbounor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:56:58 by lbounor           #+#    #+#             */
/*   Updated: 2022/11/16 11:21:42 by lbounor          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	check_border(t_data *data)
{

}

int	validate_map(t_data *data)
{
	if (check_border(data) == 1)
		return (1);
	
}
