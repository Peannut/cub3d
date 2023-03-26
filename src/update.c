/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:23:13 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/26 01:27:25 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


double fabs_val(double x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

void update(t_data *data) {
    t_player *player = &data->player;
    char **map = data->info->map;
    
    player->rotation_angle += player->turndirection * player->rotationspeed;
    player->rotation_angle = normalize_angle(player->rotation_angle);

    double dx = player->walkdirection * cos(player->rotation_angle) +
                player->sidewaysdirection * -sin(player->rotation_angle);
    double dy = player->walkdirection * sin(player->rotation_angle) +
                player->sidewaysdirection * cos(player->rotation_angle);

    double newPlayerX = player->x + dx * player->movespeed;
    double newPlayerY = player->y + dy * player->movespeed;

    int mapX = (int)(newPlayerX / BLOCK);
    int mapY = (int)(newPlayerY / BLOCK);
    
    if (map[mapY][mapX] != '1' ) {
        int x1 = (int)player->x / BLOCK;
        int y1 = (int)player->y / BLOCK;
        int x2 = (int)newPlayerX / BLOCK;
        int y2 = (int)newPlayerY / BLOCK;
        if ((x1 != x2 && y1 != y2) &&
            (map[y1][x2] == '1' && map[y2][x1] == '1') &&
            (fabs_val(newPlayerX - x2 * BLOCK) < 6 || fabs_val(newPlayerY - y2 * BLOCK) < 6)) {
            // Do not update player position
        } else {
            player->x = newPlayerX;
            player->y = newPlayerY;
        }
        // player->x = newPlayerX;
        // player->y = newPlayerY;
    };
}


void    draw_black(t_data *data)
{
    int i = -1;
    while (++i < WIN_WIDTH)
        draw_line2(data->frame, i, 0, i, WIN_HEIGHT, 0);
}

int    rgb_to_hex(int r, int g, int b)
{
    int    rgb;

    rgb = (r << 16) + (g << 8) + b;
    return (rgb);
}

void	render_ceiling(t_data *data,int wallheight, int x)
{
	int	y;
	int	endY;
    int color;

	y = 0;
	endY = (WIN_HEIGHT / 2) - wallheight / 2;
    color = rgb_to_hex(data->info->c[0], data->info->c[1], data->info->c[2]);
	while (y < endY)
	{
		my_pixel_put(data->frame, x, y, color);
		y++;
	}
}


void	render_floor(t_data *data, int wallheight,  int x)
{
	int	y;
	int	endY;
    int color;

	y = (WIN_HEIGHT / 2 + wallheight / 2) - 1;
	endY = WIN_HEIGHT;
    color = rgb_to_hex(data->info->f[0], data->info->f[1], data->info->f[2]);
	while (y < endY)
	{
		my_pixel_put(data->frame, x, y, color);
		y++;
	}
}

void render(t_data *data) {
    t_player *player = &data->player;
    draw_map(data);
    castAllRays(data);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->frame, 0, 0);
}
