/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 16:19:21 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/01/04 13:53:51 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_map(void *mlx, void *window, char map[10][10]) {
    int x, y, i, j;
    int color;

    for (y = 0; y < 10; y++) {
        for (x = 0; x < 10; x++) {
            if (map[y][x] == '1') {
                color = 0xA020F0; 
            } else {
                color = 0xFFFF00; 
            }
            for (i = 0; i < 32; i++) {
                for (j = 0; j < 32; j++) {
                    mlx_pixel_put(mlx, window, x * 32 + i, y * 32 + j, color);
                }
            }
        }
    }
}

void draw_grid(void *mlx, void *window) {
    int x, y, i, j;

    for (y = 0; y < 10; y++) {
        for (x = 0; x < 10; x++) {
            // draw grid
            for (i = 0; i < 32; i++) {
                mlx_pixel_put(mlx, window, x * 32 + i, y * 32 + 31, 0x000000);
            }
            for (j = 0; j < 32; j++) {
                mlx_pixel_put(mlx, window, x * 32 + 31, y * 32 + j, 0x000000);
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
                mlx_pixel_put(mlx, window, x + i - radius, y + j - radius, color);
            }
        }
    }
}

void draw_player(void *mlx, void *window, t_data *data) {
    printf("player.x = %f, player.y = %f\n", data->player.x, data->player.y);
    int radius = 3;  // radius of the circle
    int center_x = data->player.x * 32 + 16;  // x coordinate of the center of the circle
    int center_y = data->player.y * 32 + 16;  // y coordinate of the center of the circle
    int color = 0xFF0000;  // color of the circle

    draw_circle(mlx, window, center_x, center_y, radius, color);
}
