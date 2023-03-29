/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_rays_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:42:26 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/29 18:00:24 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double	normalize_angle(double angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

int	find_ray_facing_up(t_ray *ray)
{
	if (ray->ray_angle < 2 * M_PI && ray->ray_angle > M_PI)
		return (1);
	return (0);
}

int	find_ray_facing_right(t_ray *ray)
{
	if (ray->ray_angle < M_PI / 2 || ray->ray_angle > 3 * M_PI / 2)
		return (1);
	return (0);
}

void	find_ray_face(t_data *data, int ray)
{
	data->rays[ray].ray_facing_up = find_ray_facing_up(&data->rays[ray]);
	data->rays[ray].ray_facing_down = !data->rays[ray].ray_facing_up;
	data->rays[ray].ray_facing_right = find_ray_facing_right(&data->rays[ray]);
	data->rays[ray].ray_facing_left = !data->rays[ray].ray_facing_right;
}

double	distancecalc(t_player valone, t_vec valtwo)
{
	double	sum_x;
	double	sum_y;

	sum_x = pow(valone.x - valtwo.x, 2);
	sum_y = pow(valone.y - valtwo.y, 2);
	return (sqrt(sum_x + sum_y));
}

int	get_color_from_texture(t_data *data, int y, int ray, int wallheight)
{
	t_img	tex;
	int		h;

	tex.addr = mlx_get_data_addr(data->text, &tex.bits_per_pixel,
			&tex.line_length, &tex.endian);
	if (data->rays[ray].hit_horizontal)
		tex.addr += ((int)((double)y * ((double)BLOCK / (double)wallheight))
				* tex.line_length) + ((data->rays[ray].hitx % BLOCK)
				* (tex.bits_per_pixel / 8));
	else
		tex.addr += ((int)((double)y * ((double)BLOCK / (double)wallheight))
				* tex.line_length) + ((data->rays[ray].hity % BLOCK)
				* (tex.bits_per_pixel / 8));
	return (*(int *)tex.addr);
}