/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ext.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leo <Leo@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:06:55 by Leo               #+#    #+#             */
/*   Updated: 2022/11/09 13:07:18 by Leo              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_ext(char *str, char *ext)
{
	char	*tmp;

	tmp = ft_strstr(str, ext);
	if (!tmp)
		return (0);
	if (ft_strcmp(tmp, ext))
		return (0);
	return (1);
}
