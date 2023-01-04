/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:59:56 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/01/05 00:21:00 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include "cub3d.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void re_render(t_data *data) {
    t_player *player = &data->player;

    mlx_clear_window(data->mlx, data->mlx_win);
    draw_map(data->mlx, data->mlx_win, data);
    draw_player(data->mlx, data->mlx_win, data);
    mlx_do_sync(data->mlx);
}

void    update(t_data *data) {
    t_player *player = &data->player;
    char **map = data->map;

    // update player's rotation
    player->rotationAngle += player->turnDirection * player->rotationSpeed;

    // update player's position
    double moveStep = player->walkDirection * player->moveSpeed;
    double newPlayerX = player->x + cos(player->rotationAngle) * moveStep;
    double newPlayerY = player->y + sin(player->rotationAngle) * moveStep;

    // check if the new position is inside a wall
    if (map[(int)newPlayerY][(int)newPlayerX] == '0') {
        player->x = newPlayerX;
        player->y = newPlayerY;
    }
}

void draw_line(void *mlx, void *window, t_data *data) {
    int x1 = data->player.x * 32 + 16;  // x coordinate of the player's position
    int y1 = data->player.y * 32 + 16;  // y coordinate of the player's position
    int x2 = x1 + 40 * cos(data->player.rotationAngle);  // x coordinate of the end of the line
    int y2 = y1 + 40 * sin(data->player.rotationAngle);  // y coordinate of the end of the line
    int color = 0x0000FF;  // color of the line

    // draw line
    int i;
    for (i = 0; i < 40; i++) {
        int x = x1 + i * cos(data->player.rotationAngle);
        int y = y1 + i * sin(data->player.rotationAngle);
        mlx_pixel_put(mlx, window, x, y, color);
    }
}

int key_press(int keycode, void *param) {
    t_data *data = (t_data*)param;
    t_player *player = &data->player;
    void *mlx = data->mlx;
    void *window = data->mlx_win;
    char **map = data->map;

    double moveStep;

    if (keycode == 119) {  // W key
       player->walkDirection = 1;
    } else if (keycode == 97) {  // A key
        player->turnDirection = -1;
    } else if (keycode == 115) {  // S key
      player->walkDirection = -1;
    } else if (keycode == 100) {  // D key
        player->turnDirection = 1;
      
    }
    printf("turnDirection: %d\n", player->turnDirection);
    // update(data);
    // draw_line(mlx, window, data);
    // re_render(data);
    // re-render the map and player
    // render(data);

    return (0);
}


int key_release(int keycode, void *param) {
    t_data *data = (t_data*)param;  
    t_player *player = &data->player;  
    void *mlx = data->mlx;  
    void *window = data->mlx_win;  
    char **map = data->map;

    if (keycode == 119) {  // W key
        player->walkDirection = 0;
    } else if (keycode == 97) {  // A key
        player->turnDirection = 0;
    } else if (keycode == 115) {  // S key
        player->walkDirection = 0;
    } else if (keycode == 100) {  // D key
        player->turnDirection = 0;
    }
    return (0);
}



int main(int ac, char **av)
{
	//test2
   if (ac != 2)
   {
        printf("usage : cub3d ./file.cub\n");
        exit(1);
   }
//     init_the_map(av[1]);
    void	*mlx;
	void	*mlx_win;
    // t_player player;
    t_data data;
    data.player.x = 2;
    data.player.y = 5;
    data.player.turnDirection = 0;
    data.player.walkDirection = 0;
    data.player.rotationAngle = PI / 2;
    data.player.rotationSpeed = 3 * (PI / 180);
    data.player.moveSpeed = 4.0;
    data.map = readingdata(av[1]);
    data.height = countlines(av[1]);
    data.width = countwidth(av[1]);
    
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, (data.width - 1)* BLOCK, data.height * BLOCK, "Hello world!");
    draw_map(data.mlx, data.mlx_win, &data);
    draw_grid(data.mlx, data.mlx_win, &data);
    draw_player(data.mlx, data.mlx_win, &data);
    draw_line(data.mlx, data.mlx_win, &data);
    // t_player_params params;
    // params.player = &player;
    // data.map = map;
    mlx_hook(data.mlx, 2, 1L << 0, key_press, (void*)&data);
    mlx_hook(data.mlx, 3, 1L << 1, key_release, (void*)&data);
    mlx_loop(data.mlx);

    return (0);
}