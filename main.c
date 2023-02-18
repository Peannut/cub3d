/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:59:56 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/02/18 03:06:17 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_line(t_data *data) {
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
        // mlx_pixel_put(data->mlx, data->mlx_win, x, y, color);
        my_pixel_put(data->frame, x, y, color);
    }
}

int key_press(int keycode, void *param) {
    t_data *data = (t_data*)param;
    t_player *player = &data->player;
    char **map = data->map;

    double moveStep;
    
    if (keycode == 13) {  // W key
       player->walkDirection = 1;
    } else if (keycode == 0) {  // A key
        player->sidewaysDirection = -1;
    } else if (keycode == 1) {  // S key
      player->walkDirection = -1;
    } else if (keycode == 2) {  // D key
        player->sidewaysDirection = 1;
    }
    else if (keycode == 124){ // right arrow
        player->turnDirection = 1;
    }
    else if (keycode == 123){ // left arrow
        player->turnDirection = -1;
    }
    else if (keycode == 53){
        exit(1);
    }
    // printf("turnDirection: %d\n", player->turnDirection);
    update(data);
    render(data);

    return (0);
}


int key_release(int keycode, void *param) {
    t_data *data = (t_data*)param;  
    t_player *player = &data->player;
    char **map = data->map;
    if (keycode == 13) {  // W key
       player->walkDirection = 0;
    } else if (keycode == 0) {  // A key
        player->sidewaysDirection = 0;
    } else if (keycode == 1) {  // S key
      player->walkDirection = 0;
    } else if (keycode == 2) {  // D key
        player->sidewaysDirection = 0;
    }
    else if (keycode == 124){ // right arrow
        player->turnDirection = 0;
    }
    else if (keycode == 123){ // left arrow
        player->turnDirection = 0;
    }
    return (0);
}



int main(int ac, char **av)
{
   if (ac != 2)
   {
        printf("usage : cub3d ./file.cub\n");
        exit(1);
   }
//     init_the_map(av[1]);
    // t_player player;
    t_data data;
    data.player.x = 2; //changed them in is_valid()
    data.player.y = 5;
    data.player.turnDirection = 0;
    data.player.walkDirection = 0;
    data.player.rotationAngle = PI / 2;
    data.player.rotationSpeed = 3 * (PI / 180);
    data.player.moveSpeed = 0.1;
    data.map = readingdata(av[1], &data);
    data.height = countlines(av[1]);
    data.width = countwidth(av[1]);
    
    
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Peanut cub3d!");
    data.frame = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
    draw_map(&data);
    draw_grid(&data);
    draw_player(&data , 1);
    draw_line(&data);
    mlx_put_image_to_window(data.mlx, data.mlx_win, data.frame, 0, 0);
    // t_player_params params;
    // params.player = &player;
    // data.map = map;
    mlx_hook(data.mlx_win, 2, 0, key_press, (void*)&data);
    mlx_hook(data.mlx_win, 3, 0, key_release, (void*)&data);
    mlx_hook(data.mlx_win, 17, 0, exitfunc, NULL);
    mlx_loop(data.mlx);
    return (0);
}