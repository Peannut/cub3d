/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:59:56 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/18 15:48:43 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_line2(void *img, double x1, double y1, double x2, double y2, int color)
{
    double distance;
    double midx;
    double midy;
    double d_midx;
    double d_midy;

    midx = 0;
	midy = 0;
	distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	d_midx = (x2 - x1) / distance;
	d_midy = (y2 - y1) / distance;
	while (distance-- > 0)
	{
		my_pixel_put(img, (int)(x1 + midx), (int)(y1 + midy), color);
		midx += d_midx;
		midy += d_midy;
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
	//test2
	if (ac != 2)
	{
		printf("usage : cub3d ./file.cub\n");
		exit(1);
	}
    // init_the_map(av[1]);
    // t_player player;
	t_data data;
	data.player.turnDirection = 0;
	data.player.walkDirection = 0;
    data.player.sidewaysDirection = 0;
	data.player.rotationAngle = 0;
	data.player.rotationSpeed = 4 * (PI / 180);
	data.player.moveSpeed = 5;
	data.map = readingdata(av[1]);
	data.height = countlines(av[1]);
	data.width = countwidth(av[1]);
    
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Peanut cub3d!");
	data.frame = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
    int i;
    data.text = mlx_xpm_file_to_image(data.mlx, "north.xpm", &i, &i);
	draw_map(&data);
	// draw_grid(&data);
	draw_player(&data , 1);
	draw_line2(data.frame, data.player.x, data.player.y, (data.player.x) + cos(data.player.rotationAngle) * 40, (data.player.y) + sin(data.player.rotationAngle) * 40, 0x0000FF);
	// draw_line(&data);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.frame, 0, 0);
    // t_player_params params;
    // params.player = &player;
    // data.map = map;
	mlx_hook(data.mlx_win, 2, 0, key_press, (void*)&data);
	mlx_hook(data.mlx_win, 3, 0, key_release, (void*)&data);
    mlx_hook(data.mlx_win, 6, 0 , &mouse_event, (void*)&data);
	mlx_hook(data.mlx_win, 17, 0, exitfunc, NULL);
	mlx_loop(data.mlx);
    return (0);
}