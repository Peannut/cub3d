/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:59:56 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/01/04 15:03:53 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include "cub3d.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int key_press(int keycode, void *param) {
    printf("key pressed: %d\n", keycode);
    // t_data *data = (t_data*)param;  // cast the void pointer to a t_data pointer
    // t_player *player = &data->player;  // get a pointer to the player struct
    // void *mlx = data->mlx;  // get a pointer to the mlx variable
    // void *window = data->window;  // get a pointer to the window variable
    // char (*map)[10] = data->map;  // get a pointer to the map array

    double moveStep;
    if (keycode == 119) {  // W key

    }
	else if (keycode == 97) {  // A key
      
    }
	else if (keycode == 115) {  // S key
      
    }
	else if (keycode == 100) {  // D key
      
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
    draw_player(mlx, mlx_win, &data);
    // t_player_params params;
    // params.player = &player;
    // data.map = map;
    // mlx_hook(mlx_win, 2, 1L << 0, key_press, (void*)&data);
   
	mlx_loop(mlx);
    return (0);
}