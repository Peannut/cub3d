/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 16:19:21 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/28 17:08:16 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	my_pixel_put(void *img, int x, int y, int color)
{
	t_img	img_addr;
	char	*pos;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	img_addr.addr = mlx_get_data_addr(img, &img_addr.bits_per_pixel,
			&img_addr.line_length, &img_addr.endian);
	pos = img_addr.addr + ((y * img_addr.line_length) + (x
				* (img_addr.bits_per_pixel / 8)));
	*(unsigned int *)pos = color;
}

void	draw_player(t_data *data, int flag)
{
	int	i;
	int	j;

	i = 0;
	if (flag == 1)
	{
		while (i < data->height)
		{
			j = 0;
			while (j < data->width)
			{
				if (data->info->map[i][j] == data->player.spawn)
				{
					data->player.x = j * BLOCK + BLOCK / 2 + 1;
					data->player.y = i * BLOCK + BLOCK / 2 + 1;
					break ;
				}
				j++;
			}
			i++;
		}
	}
}
