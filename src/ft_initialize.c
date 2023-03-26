/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:17:04 by abouhaga          #+#    #+#             */
/*   Updated: 2023/03/26 02:17:45 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	initialize(t_info *info)
{
	info->no = 0;
	info->so = 0;
	info->we = 0;
	info->ea = 0;
	info->f = 0;
	info->c = 0;
}

t_tools	initialize_tools(void)
{
	t_tools	tool;

	tool.no = 0;
	tool.so = 0;
	tool.we = 0;
	tool.ea = 0;
	tool.f = 0;
	tool.c = 0;
	return (tool);
}
