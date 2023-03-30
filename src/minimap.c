/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:50:52 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/30 16:20:22 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_minimap_square(t_data *data, t_minimap *minimap, int x, int y)
{
	int	mapx;
	int	mapy;
	int	color;
	int	i;
	int	j;

	mapx = minimap->centerx + (x - data->player.x / BLOCK) * BLOCK / 2;
	mapy = minimap->centery + (y - data->player.y / BLOCK) * BLOCK / 2;
	color = get_map_color(data->info->map[y][x]);
	i = 0;
	while (i < BLOCK / 2)
	{
		j = 0;
		while (j < BLOCK / 2)
		{
			if ((mapx + i - minimap->centerx) * (mapx + i - minimap->centery)
				+ (mapy + j - minimap->centery) * (mapy + j
					- minimap->centery) <= minimap->radius * minimap->radius)
			{
				my_pixel_put(data->frame, mapx + i, mapy + j, color);
			}
			j++;
		}
		i++;
	}
}

void	draw_visible_map(t_data *data, t_minimap *minimap)
{
	int	x;
	int	y;

	x = minimap->startx;
	while (x <= minimap->endx)
	{
		y = minimap->starty;
		while (y <= minimap->endy)
		{
			draw_minimap_square(data, minimap, x, y);
			y++;
		}
		x++;
	}
}

void	draw_player_on_minimap(t_data *data, t_minimap *minimap)
{
	int		i;
	int		j;
	t_vec	var;
	t_vec	varone;

	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			if (i * i + j * j <= 4)
				my_pixel_put(data->frame, minimap->centerx + i, minimap->centery
					+ j, 0xFF0000);
			j++;
		}
		i++;
	}
	var.x = minimap->centerx + cos(data->player.rotation_angle) * 15;
	var.y = minimap->centery + sin(data->player.rotation_angle) * 15;
	varone.x = minimap->centerx;
	varone.y = minimap->centery;

	draw_line2(data->frame, &varone, &var, 0xFF0000);
}

void	draw_map(t_data *data)
{
	t_minimap	minimap;

	minimap = init_minimap();
	calculate_visible_map(data, &minimap);
	draw_minimap_circle(data, &minimap);
	draw_visible_map(data, &minimap);
	draw_player_on_minimap(data, &minimap);
}
