/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:46:37 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/30 16:01:00 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void draw_line2(t_data *data, double x1, double y1, double x2, double y2)
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
		my_pixel_put(data->frame, (int)(x1 + midx), (int)(y1 + midy),
			data->color);
		midx += d_midx;
		midy += d_midy;
	}
}

int	key_press(int keycode, void *param)
{
	t_data		*data;
	t_player	*player;

	data = (t_data *)param;
	player = &data->player;
	if (keycode == 13)
		player->walkdirection = 1;
	else if (keycode == 0)
		player->sidewaysdirection = -1;
	else if (keycode == 1)
		player->walkdirection = -1;
	else if (keycode == 2)
		player->sidewaysdirection = 1;
	else if (keycode == 124)
		player->turndirection = 1;
	else if (keycode == 123)
		player->turndirection = -1;
	else if (keycode == 53)
		exit(1);
	update(data);
	render(data);
	return (0);
}


int	key_release(int keycode, void *param)
{
	t_data		*data;
	t_player	*player;

	data = (t_data *)param;
	player = &data->player;
	if (keycode == 13)
		player->walkdirection = 0;
	else if (keycode == 0)
		player->sidewaysdirection = 0;
	else if (keycode == 1)
		player->walkdirection = 0;
	else if (keycode == 2)
		player->sidewaysdirection = 0;
	else if (keycode == 124)
		player->turndirection = 0;
	else if (keycode == 123)
		player->turndirection = 0;
	return (0);
}

void	init_rotationangel(t_data *data)
{
	data->player.turndirection = 0;
	data->player.walkdirection = 0;
	data->player.sidewaysdirection = 0;
	data->player.rotationspeed = 4 * (PI / 180);
	data->player.movespeed = 6;
	data->fov = FOV_ANGEL * (M_PI / 180);
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