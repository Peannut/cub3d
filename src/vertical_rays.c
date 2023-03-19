/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:05:42 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/18 20:47:03 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void	hitsave(t_data *data,bool val1 , bool val2,int ray)
{
	data->rays[ray].HitHorizontal = val1;
	data->rays[ray].HitVertical = val2;
}

void	findverticalsteps(t_data *data,t_vec *intercept, t_vec *step, int ray)
{

	intercept->x = (floor(data->player.x / BLOCK) * BLOCK);
	if (data->rays[ray].rayFacingRight)
		intercept->x += BLOCK;
	intercept->y = data->player.y + (intercept->x - data->player.x) * tan(data->rays[ray].rayAngle);
	// finding stepx and stepy;
	while (intercept->y > 0 && intercept->y / BLOCK < data->height && intercept->x > 0 && intercept->x / BLOCK < data->width)
	{
		// intercept->x = (floor(data->player.x / BLOCK) * BLOCK);
		if ((data->rays[ray].rayFacingRight && data->info->map[(int)(intercept->y / BLOCK)][(int)(intercept->x / BLOCK)] == '1')
            || (data->rays[ray].rayFacingLeft && data->info->map[(int)(intercept->y / BLOCK)][(int)(intercept->x / BLOCK) - 1] == '1'))
            break ;
		if (data->rays[ray].rayFacingRight)
			intercept->x += BLOCK;
		else
			intercept->x -= BLOCK;
		intercept->y = data->player.y + (intercept->x - data->player.x) * tan(data->rays[ray].rayAngle);
	}
}

// double vertical_rays(t_data *data, int ray)
t_vec vertical_rays(t_data *data, int ray)
{
	t_vec intercept;
	t_vec step;


	findverticalsteps(data, &intercept, &step, ray);
	
	return (intercept);
}