/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 16:19:21 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/02/26 22:49:08 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_pixel_put(void *img, int x, int y, int color)
{
	t_img img_addr;
    char *pos;
    if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
        return ;
    img_addr.addr = mlx_get_data_addr(img, &img_addr.bits_per_pixel, &img_addr.line_length, &img_addr.endian);
    pos = img_addr.addr + ((y * img_addr.line_length) + (x * (img_addr.bits_per_pixel / 8)));
    *(unsigned int *)pos = color;
}

void draw_map(t_data *data) {
    int x, y, i, j;
    int color;

    for (y = 0; y < data->height; y++) {
        for (x = 0; x < data->width; x++) {
            if (data->info.map[y][x] == '1') {
                color = 0xA020F0; 
            } else {
                color = 0xFFFF00; 
            }
            for (i = 0; i < 32; i++) {
                for (j = 0; j < 32; j++) {
                    // mlx_pixel_put(data->mlx, data->mlx_win, x * BLOCK + i, y * BLOCK + j, color);
                    my_pixel_put(data->frame, x * BLOCK + i, y * BLOCK + j, color);
                }
            }
        }
    }
}

void draw_grid(t_data *data) {
    int x, y, i, j;

    for (y = 0; y < data->height; y++) {
        for (x = 0; x < data->width; x++) {
            // draw grid
            for (i = 0; i < 32; i++) {
                // mlx_pixel_put(data->mlx, data->mlx_win, x * 32 + i, y * 32 + 31, 0x000000);
                my_pixel_put(data->frame, x * 32 + i, y * 32 + 31, 0x000000);
            }
            for (j = 0; j < 32; j++) {
                // mlx_pixel_put(data->mlx, data->mlx_win, x * 32 + 31, y * 32 + j, 0x000000);
                my_pixel_put(data->frame, x * 32 + 31, y * 32 + j, 0x000000);
            }
        }
    }
}

void draw_circle(void *mlx, void *window, int x, int y, int radius, int color) {
    int i, j;

    // draw circle
    for (i = 0; i < 2 * radius; i++) {
        for (j = 0; j < 2 * radius; j++) {
            // if the pixel is within the circle, draw it
            if ((i - radius) * (i - radius) + (j - radius) * (j - radius) <= radius * radius) {
                // mlx_pixel_put(mlx, window, x + i - radius, y + j - radius, color);
                my_pixel_put(window, x + i - radius, y + j - radius, color);
            }
        }
    }
}

// void draw_player(void *mlx, void *window, t_data *data) {
//     int radius = 3;  // radius of the circle
//     int center_x = data->player.x * 32 + 16;  // x coordinate of the center of the circle
//     int center_y = data->player.y * 32 + 16;  // y coordinate of the center of the circle
//     int color = 0xFF0000;  // color of the circle

//     draw_circle(mlx, window, center_x, center_y, radius, color);
// }

void draw_player(t_data *data , int flag) {
    int radius = 3;  // radius of the circle
    int color = 0xFF0000;  // color of the circle
    int i, j;

    // find the position of the 'P' character in the map
    if (flag == 1)
    {
        for (i = 0; i < data->height; i++) {
            for (j = 0; j < data->width; j++) {
                if (data->info.map[i][j] == 'P') {
                    data->player.x = j;
                    data->player.y = i;
                    break;
                }
            }
    }
    }
   
    // calculate the center of the circle
    int center_x = data->player.x * BLOCK + 16;
    int center_y = data->player.y * BLOCK + 16;

    // draw player
    // draw_circle(data->mlx, data->mlx_win, center_x, center_y, radius, color);
    draw_circle(data->mlx, data->frame, center_x, center_y, radius, color);
}