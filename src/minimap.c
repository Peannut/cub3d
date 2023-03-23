/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:50:52 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/23 19:55:04 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void draw_map(t_data *data) {
//     int x, y, i, j;
//     int color;

//     // calculate the visible portion of the map centered around the player
//     int startX = (int)(data->player.x / BLOCK) - 2;
//     int startY = (int)(data->player.y / BLOCK) - 2;
//     int endX = startX + 9;
//     int endY = startY + 9;
//     startX = (startX < 0) ? 0 : startX;
//     startY = (startY < 0) ? 0 : startY;
//     endX = (endX >= data->width) ? data->width - 1 : endX;
//     endY = (endY >= data->height) ? data->height - 1 : endY;

//     for (y = startY; y <= endY; y++) {
//         for (x = startX; x <= endX; x++) {
//             if (data->map[y][x] == '1') {
//                 color = 0xA020F0; 
//             } else {
//                 color = 0xFFFF00; 
//             }
//             for (i = 0; i < BLOCK; i++) {
//                 for (j = 0; j < BLOCK; j++) {
//                     // mlx_pixel_put(data->mlx, data->mlx_win, (x - startX) * BLOCK + i, (y - startY) * BLOCK + j, color);
//                     my_pixel_put(data->frame, (x - startX) * BLOCK + i , (y - startY) * BLOCK + j , color);
//                 }
//             }
//         }
//     }

//     // draw player at the center of the view
//     int playerX = (int)(data->player.x) - startX * BLOCK;
//     int playerY = (int)(data->player.y) - startY * BLOCK;
//     for (i = -1; i <= 1; i++) {
//         for (j = -1; j <= 1; j++) {
//             // mlx_pixel_put(data->mlx, data->mlx_win, playerX + i, playerY + j, 0xFF0000);
//             my_pixel_put(data->frame, playerX + i, playerY + j, 0xFF0000);
//         }
//     }
// }

void draw_map(t_data *data) {
    int x, y, i, j;
    int color;

    // calculate the visible portion of the map centered around the player
    int startX = (int)(data->player.x / BLOCK) - 6;
    int startY = (int)(data->player.y / BLOCK) - 6;
    int endX = startX + 12;
    int endY = startY + 12;
    startX = (startX < 0) ? 0 : startX;
    startY = (startY < 0) ? 0 : startY;
    endX = (endX >= data->width) ? data->width - 1 : endX;
    endY = (endY >= data->height) ? data->height - 1 : endY;

    int minimapWidth = 200;
    int minimapHeight = 200;

    // draw the minimap circle
    int minimapRadius = 100;
    int centerX = minimapWidth / 2;
    int centerY = minimapHeight / 2;
    for (y = 0; y < minimapHeight; y++) {
        for (x = 0; x < minimapWidth; x++) {
            if ((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY) <= minimapRadius * minimapRadius) {
                my_pixel_put(data->frame, x, y, 0xFFFFFF);
            }
        }
    }

    int mapX, mapY;
    for (y = startY; y <= endY; y++) {
        for (x = startX; x <= endX; x++) {
            mapX = (int)(centerX + (x - data->player.x / BLOCK) * BLOCK / 2);
            mapY = (int)(centerY + (y - data->player.y / BLOCK) * BLOCK / 2);
            if (data->info->map[y][x] == '1') {
                color = 0xA020F0; 
            }
            else if (data->info->map[y][x] == ' '){
                color = 0xFFFFFF;
            } 
            else {
                color = 0xFFFF00; 
            }
            for (i = 0; i < BLOCK / 2; i++) {
                for (j = 0; j < BLOCK / 2; j++) {
                    if ((mapX + i - centerX) * (mapX + i - centerX) + (mapY + j - centerY) * (mapY + j - centerY) <= minimapRadius * minimapRadius) {
                        my_pixel_put(data->frame, mapX + i, mapY + j, color);
                    }
                }
            }
        }
    }

    // draw player at the center of the minimap
    for (i = -2; i <= 2; i++) {
        for (j = -2; j <= 2; j++) {
            if (i * i + j * j <= 4) {
                my_pixel_put(data->frame, centerX + i, centerY + j, 0xFF0000);
            }
        }
    }
}

void	minimap_render(t_data *data)
{
	int l;

	l = 0;

	
	draw_map(data);
    // draw_grid(data);
    draw_player(data, 0);
	while (l < data->raysnumba)
	{
		draw_line2(data->frame, data->player.x, data->player.y, data->rays[l].Hitx, data->rays[l].Hity, 0x0000FF);
		l++;
	}
	
}