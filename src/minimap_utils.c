/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:41:48 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/29 14:36:43 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	calculate_visible_map(t_data *data, t_minimap *minimap)
{
	minimap->startx = (int)(data->player.x / BLOCK) - 6;
	minimap->starty = (int)(data->player.y / BLOCK) - 6;
	minimap->endx = minimap->startx + 12;
	minimap->endy = minimap->starty + 12;
	if (minimap->startx < 0)
		minimap->startx = 0;
	if (minimap->starty < 0)
		minimap->starty = 0;
	if (minimap->endx >= data->width)
		minimap->endx = data->width - 1;
	if (minimap->endy >= data->height)
		minimap->endy = data->height - 1;
}

// Function to initialize the minimap struct
t_minimap	init_minimap(void)
{
	t_minimap	minimap;

	minimap.width = 200;
	minimap.height = 200;
	minimap.centerx = minimap.width / 2;
	minimap.centery = minimap.height / 2;
	minimap.radius = 100;
	return (minimap);
}

// Function to draw the minimap circle
void	draw_minimap_circle(t_data *data, t_minimap *minimap)
{
	int	x;
	int	y;

	x = 0;
	while (x < minimap->width)
	{
		y = 0;
		while (y < minimap->height)
		{
			if ((x - minimap->centerx) * (x - minimap->centerx) + (y
					- minimap->centery) * (y
					- minimap->centery) <= minimap->radius * minimap->radius)
			{
				my_pixel_put(data->frame, x, y, 0xFFFFFF);
			}
			y++;
		}
		x++;
	}
}

int	get_map_color(char c)
{
	if (c == '1')
		return (0xA020F0);
	else if (c == ' ')
		return (0xFFFFFF);
	else
		return (0xFFFF00);
}
