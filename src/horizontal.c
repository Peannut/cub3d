/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:54:17 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/28 16:54:23 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	find_horizinsteps(t_data *data, t_vec *intercept,
		int ray)
{
	intercept->y = (floor(data->player.y / BLOCK)) * BLOCK;
	if (data->rays[ray].ray_facing_down)
		intercept->y += BLOCK;
	intercept->x = data->player.x + (intercept->y - data->player.y)
		/ tan(data->rays[ray].ray_angle);
	while (intercept->y > 0 && intercept->y / BLOCK < data->height
		&& intercept->x > 0 && intercept->x / BLOCK < data->width)
	{
		if ((data->rays[ray].ray_facing_down
				&& data->info->map[(int)(intercept->y
					/ BLOCK)][(int)(intercept->x / BLOCK)] == '1')
			|| (data->rays[ray].ray_facing_up
				&& data->info->map[(int)(intercept->y / BLOCK)
				- 1][(int)(intercept->x / BLOCK)] == '1'))
			break ;
		if (data->rays[ray].ray_facing_down)
			intercept->y += BLOCK;
		else
			intercept->y -= BLOCK;
		intercept->x = data->player.x + (intercept->y - data->player.y)
			/ tan(data->rays[ray].ray_angle);
	}
}

t_vec	horizontal_ray(t_data *data, int ray)
{
	t_vec	intercept;

	find_horizinsteps(data, &intercept, ray);
	return (intercept);
}
