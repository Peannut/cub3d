/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:27:15 by abouhaga          #+#    #+#             */
/*   Updated: 2023/03/26 02:27:28 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_floor(char *map, t_info *info)
{
	if (!info->f)
		info->f = ft_check_colors(map);
}

void	ft_ceilling(char *map, t_info *info)
{
	if (!info->c)
		info->c = ft_check_colors(map);
}
