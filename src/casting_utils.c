/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_utils.c                      			    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:51:30 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/29 17:52:02 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	find_distance(t_data *data, int i)
{
	t_vec	hor_cord;
	t_vec	ver_cord;
	t_vec	distance;

	find_ray_face(data, i);
	hor_cord = horizontal_ray(data, i);
	ver_cord = vertical_rays(data, i);
	if (distancecalc(data->player, hor_cord) < distancecalc(data->player,
			ver_cord))
	{
		distance = hor_cord;
		hitsave(data, true, false, i);
	}
	else if (distancecalc(data->player,
			hor_cord) > distancecalc(data->player, ver_cord))
	{
		distance = ver_cord;
		hitsave(data, false, true, i);
	}
	else
		hitsave(data, false, false, i);
	data->rays[i].distance = distancecalc(data->player, distance);
	data->rays[i].hitx = distance.x;
	data->rays[i].hity = distance.y;
}

void	cast_all_rays(t_data *data)
{
	int		i;
	double	ray_angle;

	i = 0;
	data->raysnumba = WIN_WIDTH;
	ray_angle = data->player.rotation_angle - (data->fov / 2);
	while (i < data->raysnumba)
	{
		data->rays[i].ray_angle = normalize_angle(ray_angle);
		find_distance(data, i);
		ray_angle += (double)data->fov / (double)data->raysnumba;
		i++;
	}
	projection(data);
	draw_map(data);
}

int	exitfunc(t_data *data)
{
	(void)data;
	printf("je exit baye hh\n");
	exit(0);
}

void	*get_texture(char *file, t_data *data)
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
	else if (height != BLOCK || width != BLOCK)
	{
		printf("texture size incompatible %s\n", file);
		exit(1);
	}
	return (textur);
}
