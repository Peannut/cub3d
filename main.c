/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:59:56 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/01/04 22:17:13 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include "cub3d.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

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

void render(t_data *data) {
    void *mlx = data->mlx;
    void *window = data->window;
    t_player *player = &data->player;

    // clear the window
    mlx_clear_window(mlx, window);

    // draw the map
    draw_map(mlx, window, data);

    // draw the player
    draw_player(mlx, window, data);

    // update the window
    mlx_do_sync(mlx);
}

int key_press(int keycode, void *param) {
    t_data *data = (t_data*)param;
    t_player *player = &data->player;
    void *mlx = data->mlx;
    void *window = data->window;
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
    // re-render the map and player
    // render(data);

    return (0);
}

// int key_press(int keycode, void *param) {
//     // t_data *data = (t_data*)param;  // cast the void pointer to a t_data pointer
//     // t_player *player = &data->player;  // get a pointer to the player struct
//     // void *mlx = data->mlx;  // get a pointer to the mlx variable
//     // void *window = data->window;  // get a pointer to the window variable
//     // char **map = data->map;  // get a pointer to the map array

//     // double moveStep;

//     // if (keycode == 119) {  // W key
//     //     // move the player forward
//     //     moveStep = player->moveSpeed * cos(player->rotationAngle);
//     //     if (map[(int)(player->y + moveStep)][(int)player->x] == '0') {
//     //         player->y += moveStep;
//     //     }
//     //     moveStep = player->moveSpeed * sin(player->rotationAngle);
//     //     if (map[(int)player->y][(int)(player->x + moveStep)] == '0') {
//     //         player->x += moveStep;
//     //     }
//     // } else if (keycode == 97) {  // A key
//     //     // rotate the player to the left
//     //     player->rotationAngle -= player->rotationSpeed;
//     // } else if (keycode == 115) {  // S key
//     //     // move the player backward
//     //     moveStep = player->moveSpeed * cos(player->rotationAngle);
//     //     if (map[(int)(player->y - moveStep)][(int)player->x] == '0') {
//     //         player->y -= moveStep;
//     //     }
//     //     moveStep = player->moveSpeed * sin(player->rotationAngle);
//     //     if (map[(int)player->y][(int)(player->x - moveStep)] == '0') {
//     //         player->x -= moveStep;
//     //     }
//     // } else if (keycode == 100) {  // D key
//     //     // rotate the player to the right
//     //     player->rotationAngle += player->rotationSpeed;
//     // }
//     // printf("player x, player y: %f, %f\n", player->x, player->y);
//     // return (0);
// }

// int key_press(int keycode, void *param) {
//     printf("key pressed: %d\n", keycode);
//     // t_data *data = (t_data*)param;  // cast the void pointer to a t_data pointer
//     // t_player *player = &data->player;  // get a pointer to the player struct
//     // void *mlx = data->mlx;  // get a pointer to the mlx variable
//     // void *window = data->window;  // get a pointer to the window variable
//     // char (*map)[10] = data->map;  // get a pointer to the map array

//     double moveStep;
//     if (keycode == 119) {  // W key

//     }
// 	else if (keycode == 97) {  // A key
      
//     }
// 	else if (keycode == 115) {  // S key
      
//     }
// 	else if (keycode == 100) {  // D key
      
//     }
// 	return (0);
// }
int key_release(int keycode, void *param) {
    t_data *data = (t_data*)param;  // cast the void pointer to a t_data pointer
    t_player *player = &data->player;  // get a pointer to the player struct
    void *mlx = data->mlx;  // get a pointer to the mlx variable
    void *window = data->window;  // get a pointer to the window variable
    char **map = data->map;  // get a pointer to the map array

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
    
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, (data.width - 1)* BLOCK, data.height * BLOCK, "Hello world!");
    draw_map(mlx, mlx_win, &data);
    draw_grid(mlx, mlx_win, &data);
 ;
    draw_player(mlx, mlx_win, &data);
    draw_line(mlx, mlx_win, &data);
    // t_player_params params;
    // params.player = &player;
    // data.map = map;
    mlx_hook(mlx_win, 2, 1L << 0, key_press, (void*)&data);
    mlx_hook(mlx_win, 3, 1L << 1, key_release, (void*)&data);
	mlx_loop(mlx);
    return (0);
}