/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:23:13 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/18 20:25:53 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void update(t_data *data) {
//     t_player *player = &data->player;
//     char **map = data->map;

//     // printf("before x: %f, y: %f\n", player->x, player->y);
//     // update player's rotation
//     player->rotationAngle += player->turnDirection * player->rotationSpeed;

//     // update player's position
//     double moveStep = player->walkDirection * player->moveSpeed;
//     double newPlayerX = player->x + cos(player->rotationAngle) * moveStep;
//     double newPlayerY = player->y + sin(player->rotationAngle) * moveStep;

//     player->x = newPlayerX;
//     player->y = newPlayerY;
//     // printf("after x: %f, y: %f\n", player->x, player->y);
//     // printf("rotation angel val:%f\n",player->rotationAngle);
// }

void update(t_data *data) {
    t_player *player = &data->player;
    char **map = data->info->map;
    
//     // printf("PLAYER Y:%f AND X%f\n",player->y*BLOCK, player->x*BLOCK);
//     // update player's rotation
//     player->rotationAngle += player->turnDirection * player->rotationSpeed;
//     player->rotationAngle = normalizeAngle(player->rotationAngle);
//     // update player's position
//     double  moveStep = player->walkDirection * player->moveSpeed;
//     double  sidewaysStep = player->sidewaysDirection * player->moveSpeed;

//     double  newPlayerX = player->x + cos(player->rotationAngle) * moveStep;
//     double  newPlayerY = player->y + sin(player->rotationAngle) * moveStep;
//     newPlayerX += -sin(player->rotationAngle) * sidewaysStep;
//     newPlayerY += cos(player->rotationAngle) * sidewaysStep;
//    if (data->map[(int)player->x / BLOCK][(int)player->y / BLOCK] != '1')
//    {
//         player->x = newPlayerX;
//         player->y = newPlayerY;
//    } 
    player->rotationAngle += player->turnDirection * player->rotationSpeed;
    player->rotationAngle = normalizeAngle(player->rotationAngle);

    // calculate new player position in x direction
    double dx = player->walkDirection * cos(player->rotationAngle) +
                player->sidewaysDirection * -sin(player->rotationAngle);
    double dy = player->walkDirection * sin(player->rotationAngle) +
                player->sidewaysDirection * cos(player->rotationAngle);

    // calculate new player position
    double newPlayerX = player->x + dx * player->moveSpeed;
    double newPlayerY = player->y + dy * player->moveSpeed;

    // check if the new position is inside a wall
    int mapX = (int)(newPlayerX / BLOCK);
    int mapY = (int)(newPlayerY / BLOCK);
    if (map[mapY][mapX] != '1') {
        player->x = newPlayerX;
        player->y = newPlayerY;
    }

}

void    draw_black(t_data *data)
{
    int i = -1;
    while (++i < WIN_WIDTH)
        draw_line2(data->frame, i, 0, i, WIN_HEIGHT, 0);
}

void	draw_ceiling_and_floor(t_data *data)
{
	int x;
	int y;

	// Draw ceiling
	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			my_pixel_put(data->frame, x, y, 0x63d1f2);
			x++;
		}
		y++;
	}

	// Draw floor
	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			// my_pixel_put(data->frame, x, y, 0x41e022);
			my_pixel_put(data->frame, x, y, 0);
			x++;
		}
		y++;
	}
}

void	render_ceiling(t_data *data, int x, int wallHeight)
{
	int	y;
	int	end;

	y = 0;
	end = (WIN_HEIGHT / 2) - wallHeight / 2;
	while (y < end)
	{
		my_pixel_put(data, x, y, 0x63d1f2);
		y++;
	}
}

void	render_floor(t_data *data, int x, int wallHeight)
{
	int	y;
	int	end;

	y = (WIN_HEIGHT / 2 + wallHeight / 2) - 1;
	end = WIN_HEIGHT;
	while (y < end)
	{
		my_pixel_put(data->frame, x, y, 0x41e022);
		y++;
	}
}

void render(t_data *data) {
    t_player *player = &data->player;
    // draw_black(data);
    draw_ceiling_and_floor(data);
    draw_map(data);
	draw_line2(data->frame, (data->player.x * BLOCK + 16), (data->player.y * BLOCK + 16), (data->player.x * BLOCK + 16) + cos(data->player.rotationAngle) * 40, (data->player.y * BLOCK + 16) + sin(data->player.rotationAngle) * 40, 0x0000FF);
    // printf("x and y %f %f in bixels\n ", player->x * BLOCK + 16, player->y * BLOCK + 16);
    // draw_line(data);
    // draw_grid(data);
    draw_player(data, 0);
    castAllRays(data);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->frame, 0, 0);
    // mlx_do_sync(data->mlx);
}
