/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:19:39 by abouhaga          #+#    #+#             */
/*   Updated: 2023/03/27 16:48:43 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_extract_data(t_tools *tl, t_info *info, char **map, int i)
{
	int	j;

	j = skip_whitespace(map[i]);
	if (!tl->no && (map[i][j] == 'N'
		&& map[i][j + 1] == 'O' && map[i][j + 2] == ' '))
		(north(map[i], info), tl->counter++, tl->no = 1);
	else if (!tl->so && (map[i][j] == 'S'
		&& map[i][j + 1] == 'O' && map[i][j + 2] == ' '))
		(south(map[i], info), tl->counter++, tl->so = 1);
	else if (!tl->we && (map[i][j] == 'W'
		&& map[i][j + 1] == 'E' && map[i][j + 2] == ' '))
		(west(map[i], info), tl->counter++, tl->we = 1);
	else if (!tl->ea && (map[i][j] == 'E'
		&& map[i][j + 1] == 'A' && map[i][j + 2] == ' '))
		(east(map[i], info), tl->counter++, tl->ea = 1);
	else if (!tl->f && (map[i][j] == 'F' && map[i][j + 1] == ' '))
		(ft_floor(map[i], info), tl->counter++, tl->f = 1);
	else if (!tl->c && (map[i][j] == 'C' && map[i][j + 1] == ' '))
		(ft_ceilling(map[i], info), tl->counter++, tl->c = 1);
	return (tl->counter);
}

void	set_player_position(char c, int x, int y, t_data *data)
{
	data->player.spawn = c;
	data->player.x = x * BLOCK * BLOCK / 2;
	data->player.y = y * BLOCK * BLOCK / 2;
}

int	is_player(char c)
{
	return (c == 'N' || c == 'W' || c == 'S' || c == 'E');
}

void	valid_player(char **map, t_data *data)
{
	int	i;
	int	j;
	int	pos;

	pos = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (is_player(map[i][j]))
			{
				if (pos == 0)
					set_player_position(map[i][j], i, j, data);
				pos++;
			}
		}
	}
	if (pos != 1)
		ft_error("Map is not valid, Zero or multiple player positions !\n");
}

//Set-up the player's position
int	is_valid_component(char ch, t_data *data, int i, int j)
{
	if (ch != '1' && ch != '0' && ch != ' '
		&& ch != 'E' && ch != 'N' && ch != 'W' && ch != 'S')
		return (1);
	if (ch == 'N' || ch == 'S' || ch == 'W' || ch == 'E')
	{
		if (data->player.spawn != '+')
			ft_error("More than one player");
		data->player.x = j * BLOCK + BLOCK / 2 + 1;
		data->player.y = i * BLOCK + BLOCK / 2 + 1;
		data->player.spawn = data->info->map[i][j];
		printf("spawn in pars %c\n", data->player.spawn);
	}
	return (0);
}
