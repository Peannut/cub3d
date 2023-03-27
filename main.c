/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:59:56 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/27 17:22:31 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"

void draw_line2(void *img, double x1, double y1, double x2, double y2, int color)
{
	double	distance;
	double	midx;
	double	midy;
	double	d_midx;
	double	d_midy;

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
    char **map = data->info->map;

    double moveStep;
    
    if (keycode == 13) {  // W key
       player->walkdirection = 1;
    } else if (keycode == 0) {  // A key
        player->sidewaysdirection = -1;
    } else if (keycode == 1) {  // S key
      player->walkdirection = -1;
    } else if (keycode == 2) {  // D key
        player->sidewaysdirection = 1;
    }
    else if (keycode == 124){ // right arrow
        player->turndirection = 1;
    }
    else if (keycode == 123){ // left arrow
        player->turndirection = -1;
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
    char **map = data->info->map;
    if (keycode == 13) {  // W key
       player->walkdirection = 0;
    } else if (keycode == 0) {  // A key
		player->sidewaysdirection = 0;
    } else if (keycode == 1) {  // S key
		player->walkdirection = 0;
    } else if (keycode == 2) {  // D key
		player->sidewaysdirection = 0;
    }
    else if (keycode == 124){ // right arrow
		player->turndirection = 0;
    }
    else if (keycode == 123){ // left arrow
		player->turndirection = 0;
    }
    return (0);
}

int ft_start(char **av, t_data *cube)
{
    cube->info = ft_parse(av, cube);
        // cube->height = count_lines(cube->info->map) - cube->info->tool->counter;
        // printf("%d\n", cube->height);
        // exit(0);
    return (0);
}

size_t	ptrline(char **str)
{
	size_t	length;

	length = 0;
	while (str[length])
		length++;
	return (length);
}

int	thebiggestlen(t_data *data)
{
	int	i;
	int	max;
	int	len;

	len = 0;
	i = 0;
	max = 0;
	while (i < data->height)
	{
		len = ft_strlen(data->info->map[i]);
		if (max < len)
			max = len;
		i++;
	}
	return (max);
}

void    init_rotationAngel(t_data *data)
{
	data->player.turndirection = 0;
	data->player.walkdirection = 0;
	data->player.sidewaysdirection = 0;
	data->player.rotationspeed = 4 * (PI / 180);
	data->player.movespeed = 6;
	
	data->height = ptrline(data->info->map);
	data->width = thebiggestlen(data);
	
	if (data->player.spawn == 'S')
	    data->player.rotation_angle = M_PI / 2;
	else if (data->player.spawn == 'N')
	    data->player.rotation_angle = 3 * M_PI / 2;
	else if (data->player.spawn == 'E')
	    data->player.rotation_angle = 0;
	else if (data->player.spawn == 'W')
	    data->player.rotation_angle = M_PI;
}

int main(int ac, char **av)
{
   if (ac != 2)
   {
        printf("usage : cub3d ./file.cub\n");
        exit(1);
   }
	t_data data;
    ft_start(av, &data);
    init_rotationAngel(&data);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Peanut cub3d!");
	data.frame = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	draw_map(&data);
	// draw_grid(&data);
	draw_player(&data , 1);
	// draw_line2(data.frame, data.player.x, data.player.y, (data.player.x) + cos(data.player.rotation_angle) * 40, (data.player.y) + sin(data.player.rotation_angle) * 40, 0x0000FF);
	// draw_line(&data);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.frame, 0, 0);
    render(&data);
    // t_player_params params;
    // params.player = &player;
    // data.map = map;
	mlx_hook(data.mlx_win, 2, 0, key_press, (void*)&data);
	mlx_hook(data.mlx_win, 3, 0, key_release, (void*)&data);
    mlx_hook(data.mlx_win, 6, 0 , &mouse_event, (void*)&data);
	mlx_hook(data.mlx_win, 17, 0, exitfunc, (void*)&data);
	mlx_loop(data.mlx);
    return (0);
}