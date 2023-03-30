/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:23:13 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/30 15:35:41 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double	fabs_val(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	update_direction(t_player *player)
{
	double	dx;
	double	dy;

	player->rotation_angle += player->turndirection * player->rotationspeed;
	player->rotation_angle = normalize_angle(player->rotation_angle);
	dx = player->walkdirection * cos(player->rotation_angle)
		+ player->sidewaysdirection * -sin(player->rotation_angle);
	dy = player->walkdirection * sin(player->rotation_angle)
		+ player->sidewaysdirection * cos(player->rotation_angle);
	player->dx = dx;
	player->dy = dy;
}

int	is_valid_move(t_player *player, char **map, double x, double y)
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;

	x1 = (int)player->x / BLOCK;
	y1 = (int)player->y / BLOCK;
	x2 = (int)x / BLOCK;
	y2 = (int)y / BLOCK;
	if (x1 != x2 && y1 != y2 && map[y1][x2] == '1' && map[y2][x1] == '1')
	{
		if (fabs_val(x - x2 * BLOCK) < 6 || fabs_val(y - y2 * BLOCK) < 6)
		{
			return (0);
		}
	}
	return (1);
}

void	update_position(t_player *player, char **map)
{
	double	newplayerx;
	double	newplayery;
	int		mapx;
	int		mapy;

	newplayerx = player->x + player->dx * player->movespeed;
	newplayery = player->y + player->dy * player->movespeed;
	mapx = (int)(newplayerx / BLOCK);
	mapy = (int)(newplayery / BLOCK);
	if (map[mapy][mapx] != '1')
	{
		if (is_valid_move(player, map, newplayerx, newplayery))
		{
			player->x = newplayerx;
			player->y = newplayery;
		}
	}
}

void	update(t_data *data)
{
	t_player	*player;
	char		**map;

	player = &data->player;
	map = data->info->map;
	update_direction(player);
	update_position(player, map);
}
