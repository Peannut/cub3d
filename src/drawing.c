/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 16:19:21 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/25 15:16:31 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_pixel_put(void *img, int x, int y, int color)
{
    t_img   img_addr;
    char    *pos;
    if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
        return ;
    img_addr.addr = mlx_get_data_addr(img, &img_addr.bits_per_pixel, &img_addr.line_length, &img_addr.endian);
    pos = img_addr.addr + ((y * img_addr.line_length) + (x * (img_addr.bits_per_pixel / 8)));
    *(unsigned int *)pos = color;
}

void draw_player(t_data *data , int flag) {
    int i, j;

    // find the position of the 'P' character in the map
    if (flag == 1)
    {
        for (i = 0; i < data->height; i++) {
            for (j = 0; j < data->width; j++) {
                if (data->info->map[i][j] == data->player.spawn) {
                    data->player.x = j * BLOCK + BLOCK / 2 + 1;
                    data->player.y = i * BLOCK + BLOCK / 2 + 1;
                	printf("spawn in func %c \n", data->player.spawn);
                    break;
                }
            }
    }
    }
}