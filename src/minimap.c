/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:50:52 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/27 17:05:04 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void draw_map(t_data *data)
{
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
	int lineEndX = centerX + cos(data->player.rotation_angle) * 15;
	int lineEndY = centerY + sin(data->player.rotation_angle) * 15;
	draw_line2(data->frame, centerX, centerY, lineEndX, lineEndY, 0xFF0000);
}

void	minimap_render(t_data *data)
{
    int l;

	l = 0;

	draw_map(data);
    // draw_grid(data);
    // draw_player(data, 0);
	// while (l < data->raysnumba)
	// {
	// 	draw_line2(data->frame, data->player.x, data->player.y, data->rays[l].hitx, data->rays[l].hity, 0x0000FF);
	// 	l++;
	// }
	
}