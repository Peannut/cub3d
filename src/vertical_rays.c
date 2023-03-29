/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:05:42 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/28 17:04:26 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	hitsave(t_data *data, bool val1, bool val2, int ray)
{
	data->rays[ray].hit_horizontal = val1;
	data->rays[ray].hit_vertical = val2;
}

void	findverticalsteps(t_data *data, t_vec *intercept, int ray)
{
	intercept->x = (floor(data->player.x / BLOCK) * BLOCK);
	if (data->rays[ray].ray_facing_right)
		intercept->x += BLOCK;
	intercept->y = data->player.y + (intercept->x - data->player.x)
		* tan(data->rays[ray].ray_angle);
	while (intercept->y > 0 && intercept->y / BLOCK < data->height
		&& intercept->x > 0 && intercept->x / BLOCK < data->width)
	{
		if ((data->rays[ray].ray_facing_right
				&& data->info->map[(int)(intercept->y
					/ BLOCK)][(int)(intercept->x / BLOCK)] == '1')
			|| (data->rays[ray].ray_facing_left
				&& data->info->map[(int)(intercept->y
					/ BLOCK)][(int)(intercept->x / BLOCK) - 1] == '1'))
			break ;
		if (data->rays[ray].ray_facing_right)
			intercept->x += BLOCK;
		else
			intercept->x -= BLOCK;
		intercept->y = data->player.y + (intercept->x - data->player.x)
			* tan(data->rays[ray].ray_angle);
	}
}

t_vec	vertical_rays(t_data *data, int ray)
{
	t_vec	intercept;

	findverticalsteps(data, &intercept, ray);
	return (intercept);
}
