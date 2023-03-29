/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:21:37 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/29 18:23:27 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	rgb_to_hex(int r, int g, int b)
{
	int	rgb;

	rgb = (r << 16) + (g << 8) + b;
	return (rgb);
}

void	render_ceiling(t_data *data, int wallheight, int x)
{
	int	y;
	int	end_y;
	int	color;

	y = 0;
	end_y = (WIN_HEIGHT / 2) - wallheight / 2;
	color = rgb_to_hex(data->info->c[0], data->info->c[1], data->info->c[2]);
	while (y < end_y)
	{
		my_pixel_put(data->frame, x, y, color);
		y++;
	}
}

void	render_floor(t_data *data, int wallheight, int x)
{
	int	y;
	int	end_y;
	int	color;

	y = (WIN_HEIGHT / 2 + wallheight / 2) - 1;
	end_y = WIN_HEIGHT;
	color = rgb_to_hex(data->info->f[0], data->info->f[1], data->info->f[2]);
	while (y < end_y)
	{
		my_pixel_put(data->frame, x, y, color);
		y++;
	}
}

void	render(t_data *data)
{
	t_player	*player;

	player = &data->player;
	draw_map(data);
	cast_all_rays(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->frame, 0, 0);
}
