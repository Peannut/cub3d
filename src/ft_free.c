/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:26:26 by abouhaga          #+#    #+#             */
/*   Updated: 2023/03/27 17:06:06 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_free(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		s[i] = 0;
		i++;
	}
	free(s);
	s = NULL;
}

//to free memory allocated 
void	free_map(char **map, int num_lines)
{
	int	i;

	i = 0;
	while (i < num_lines)
	{
		free(map[i]);
		i++;
	}
	free(map);
}
