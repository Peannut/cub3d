/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 04:50:35 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/01/09 04:50:35 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double	normalizeAngle(double angle)
{
	if (angle < 0)
	{
		angle += 2 * M_PI;
	}
	if (angle >= 2 * M_PI)
	{
		angle -= 2 * M_PI;
	}
	return (angle);
}

void	find_ray_face(t_data *data, int ray)
{
	data->rays[ray].ray_facing_up = data->rays[ray].ray_angle < 2 * M_PI
			&& data->rays[ray].ray_angle > M_PI;
	data->rays[ray].ray_facing_down = data->rays[ray].ray_angle > 0
			&& data->rays[ray].ray_angle < M_PI;
	data->rays[ray].ray_facing_right = data->rays[ray].ray_angle < M_PI / 2
			|| data->rays[ray].ray_angle > 3 * M_PI / 2;
	data->rays[ray].ray_facing_left = data->rays[ray].ray_angle > M_PI / 2
			&& data->rays[ray].ray_angle < 3 * M_PI / 2;
}

void	find_Interceptions(t_data* data, t_vec* step, t_vec* intercept, int ray)
{
	intercept->y = (floor(data->player.y / BLOCK)) * BLOCK;
	if (data->rays[ray].ray_facing_down)
		intercept->y += BLOCK;
	intercept->x = data->player.x + (intercept->y - data->player.y) 
		/ tan(data->rays[ray].ray_angle);
	while (intercept->y > 0 && intercept->y / BLOCK < data->height && intercept->x > 0 && intercept->x / BLOCK < data->width)
    {
        // intercept->y = (floor(data->player.y / BLOCK)) * BLOCK;
        if ((data->rays[ray].ray_facing_down && data->info->map[(int)(intercept->y / BLOCK)][(int)(intercept->x / BLOCK)] == '1')
            || (data->rays[ray].ray_facing_up && data->info->map[(int)(intercept->y / BLOCK) - 1][(int)(intercept->x / BLOCK)] == '1'))
            break ;
        if (data->rays[ray].ray_facing_down)
            intercept->y += BLOCK;
        else
            intercept->y -= BLOCK;
        intercept->x = data->player.x + (intercept->y - data->player.y) 
            / tan(data->rays[ray].ray_angle);
    }
}

double	distancecalc(t_player valone, t_vec valtwo)
{
	double	sum_x;
	double	sum_y;

	sum_x = pow(valone.x - valtwo.x, 2);
	sum_y = pow(valone.y - valtwo.y, 2);
	return (sqrt(sum_x + sum_y));
}

t_vec	horizontal_ray(t_data *data, int ray)
{
	t_vec	step;
	t_vec	intercept;

	find_Interceptions(data, &step, &intercept, ray);
	return (intercept);
}

int	get_color_from_texture(t_data *data, int y, int ray, int wallheight)
{
	t_img	tex;
	int		h;

	tex.addr = mlx_get_data_addr(data->text, &tex.bits_per_pixel,
			&tex.line_length, &tex.endian);
	if (data->rays[ray].hit_horizontal)
		tex.addr += ((int)((double)y * ((double)BLOCK / (double)wallheight))
		* tex.line_length) + ((data->rays[ray].hitx % BLOCK) * (tex.bits_per_pixel / 8));
    else
		tex.addr += ((int)((double)y * ((double)BLOCK / (double)wallheight)) * tex.line_length) + ((data->rays[ray].hity % BLOCK) * (tex.bits_per_pixel / 8));
    return (*(int *)tex.addr);
}

void	*getTexture(char *file, t_data *data)
{
	void	*textur;
	int		width;
	int		height;

	width = 0;
	height = 0;
	textur = mlx_xpm_file_to_image(data->mlx, file, &width, &height);
	if (!textur)
	{
		printf("failed to open %s\n", file);
		exit(1);
	}
	else if (height != BLOCK || width != BLOCK )
	{
		printf("texture size incompatible %s\n", file);
		exit(1);
	}
	return (textur);
}

void    projection_draw_ray(t_data *data, int ray)
{
	int	distanceProjectionPlane;
	int	wallheight;
	int	y;
	int	color;
	int	h;
	int	end;

    if (data->rays[ray].ray_facing_up && data->rays[ray].hit_horizontal)
        data->text = getTexture(data->info->no, data);
    else if (data->rays[ray].ray_facing_down && data->rays[ray].hit_horizontal)
        data->text = getTexture(data->info->so, data);
    else if (data->rays[ray].ray_facing_left && data->rays[ray].hit_vertical)
        data->text = getTexture(data->info->we, data);
    else if (data->rays[ray].ray_facing_right && data->rays[ray].hit_vertical)
        data->text = getTexture(data->info->ea, data);
    distanceProjectionPlane = (WIN_WIDTH / 2) / (tan(FOV_ANGEL / 2));
    wallheight = (BLOCK / (data->rays[ray].distance * cos(data->player.rotation_angle - data->rays[ray].ray_angle))) * distanceProjectionPlane;
    y = 0;
    if (wallheight > WIN_HEIGHT)
	{
		y = wallheight / 2 - WIN_HEIGHT / 2;
		end = wallheight / 2 + WIN_HEIGHT / 2;
	}
	else
		end = wallheight;
    while (y < end)
	{
		color = get_color_from_texture(data, y, ray, wallheight);
		my_pixel_put(data->frame, ray, y + (WIN_HEIGHT / 2)
			- (wallheight / 2), color);
		y++;
	}
	render_ceiling(data, wallheight, ray);
	render_floor(data, wallheight, ray);
}

void    projection(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->raysnumba)
	{
		projection_draw_ray(data, i);
		++i;
	}
}

void castAllRays(t_data *data)
{
	int		i;
	double	ray_angle;
	t_vec	hor_cord;
	t_vec	ver_cord;
	t_vec	distance;

	i = 0;
	data->raysnumba = WIN_WIDTH;
	ray_angle = data->player.rotation_angle - (FOV_ANGEL / 2);
	while (i < data->raysnumba)
	{
		data->rays[i].ray_angle = normalizeAngle(ray_angle);
		find_ray_face(data, i);
		hor_cord = horizontal_ray(data, i);
		ver_cord = vertical_rays(data, i);
		if (distancecalc(data->player, hor_cord) < distancecalc(data->player, ver_cord))
		{
			distance = hor_cord;
			hitsave(data, true, false, i);
		}
		else if (distancecalc(data->player, hor_cord) > distancecalc(data->player, ver_cord))
		{
			distance = ver_cord;
			hitsave(data, false, true, i);
		}
		else
			hitsave(data, false, false, i);
		data->rays[i].distance = distancecalc(data->player, distance);
		data->rays[i].hitx = distance.x;
		data->rays[i].hity = distance.y;
		ray_angle += (double)FOV_ANGEL / (double)data->raysnumba;
		i++;
	}
	projection(data);
	minimap_render(data);
}

int	exitfunc(t_data *data)
{
	// should free hna tal mn b3d;
	(void)data;
	printf("je exit baye hh\n");
	exit(0);
}
