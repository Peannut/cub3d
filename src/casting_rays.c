/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 04:50:35 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/01/09 04:50:35 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


// void castRay(void *mlx, void *window, t_data *data, int col) {
//     int x1 = data->player.x * 32 + 16;  // x coordinate of the player's position
//     int y1 = data->player.y * 32 + 16;  // y coordinate of the player's position

//     // calculate the angle of the ray relative to the player's direction
//     double angle = data->player.rotationAngle - FOV_ANGEL / 2 + (double)col / (data->width * BLOCK )* FOV_ANGEL;

//     // find the intersection point of the ray with the closest wall
//     int x2 = x1 + 70 * cos(angle);
//     int y2 = y1 + 70 * sin(angle);

//     // draw the ray as a line
//     mlx_pixel_put(mlx, window, x1, y1, 0xFF0000);
//     mlx_pixel_put(mlx, window, x2, y2, 0xFF0000);
// }
void castRay(void *mlx, void *window, t_data *data, int col) {
    int x1 = data->player.x * BLOCK + 16;
    int y1 = data->player.y * BLOCK + 16;
    double angle = data->player.rotationAngle - FOV_ANGEL / 2 + (double)col / (data->width * BLOCK )* FOV_ANGEL;
    int x2 = x1 + 70 * cos(angle);
    int y2 = y1 + 70 * sin(angle);
    int x = x1, y = y1;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;
    int e2;

    while(x != x2 || y != y2) {
        mlx_pixel_put(mlx, window, x, y, 0xFF0000);
        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

void castAllRays(t_data *data) {
	t_player *player = &data->player;
	int scren_size = data->width;

	// int columID = 0;
	// double rays[scren_size];
	// double rayangle;
	// // start first ray substracting half of fov
	// rayangle = player->rotationAngle - (FOV_ANGEL / 2);
	printf("wsl hna\n");
	int col;
    for (col = 0; col < ((data->width - 1) * BLOCK); col++) {
        castRay(data->mlx, data->mlx_win, data, col);
    }
	printf("col value : %d\n", col);
}


void    exitfunc(void)
{
    // should free hna tal mn b3d;
    printf("je exit baye hh\n");
    exit(0);
}