/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:23:03 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/29 18:23:03 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	setup_texture(t_data *data, int ray)
{
	if (data->rays[ray].ray_facing_up && data->rays[ray].hit_horizontal)
		data->text = get_texture(data->info->no, data);
	else if (data->rays[ray].ray_facing_down && data->rays[ray].hit_horizontal)
		data->text = get_texture(data->info->so, data);
	else if (data->rays[ray].ray_facing_left && data->rays[ray].hit_vertical)
		data->text = get_texture(data->info->we, data);
	else if (data->rays[ray].ray_facing_right && data->rays[ray].hit_vertical)
		data->text = get_texture(data->info->ea, data);
}

void	calculate_wall_height(t_data *data, int ray, int *y,
int *end)
{
	int	distanceprojectionplane;

	distanceprojectionplane = (WIN_WIDTH / 2) / (tan(data->fov / 2));
	data->rays[ray].wallheight = (BLOCK / (data->rays[ray].distance
				* cos(data->player.rotation_angle - data->rays[ray].ray_angle)))
		* distanceprojectionplane;
	*y = 0;
	if (data->rays[ray].wallheight > WIN_HEIGHT)
	{
		*y = data->rays[ray].wallheight / 2 - WIN_HEIGHT / 2;
		*end = data->rays[ray].wallheight / 2 + WIN_HEIGHT / 2;
	}
	else
		*end = data->rays[ray].wallheight;
}

void	projection_draw_ray(t_data *data, int ray)
{
	int	y;
	int	end;
	int	color;

	calculate_wall_height(data, ray, &y, &end);
	setup_texture(data, ray);
	while (y < end)
	{
		color = get_color_from_texture(data, y, ray,
				data->rays[ray].wallheight);
		my_pixel_put(data->frame, ray, y + (WIN_HEIGHT / 2)
			- (data->rays[ray].wallheight / 2),
			color);
		y++;
	}
	render_ceiling(data, data->rays[ray].wallheight, ray);
	render_floor(data, data->rays[ray].wallheight, ray);
}

void	projection(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->raysnumba)
	{
		projection_draw_ray(data, i);
		++i;
	}
}

int	get_color_from_texture(t_data *data, int y, int ray, int wallheight)
{
	t_img	tex;

	tex.addr = mlx_get_data_addr(data->text, &tex.bits_per_pixel,
			&tex.line_length, &tex.endian);
	if (data->rays[ray].hit_horizontal)
		tex.addr += ((int)((double)y * ((double)BLOCK
						/ (double)wallheight))*tex.line_length)
			+ ((data->rays[ray].hitx % BLOCK) *(tex.bits_per_pixel / 8));
	else
		tex.addr += ((int)((double)y * ((double)BLOCK
						/ (double)wallheight)) *tex.line_length)
			+ ((data->rays[ray].hity % BLOCK) *(tex.bits_per_pixel / 8));
	return (*(int *)tex.addr);
}
