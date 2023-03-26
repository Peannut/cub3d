/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:11:57 by abouhaga          #+#    #+#             */
/*   Updated: 2023/03/26 02:22:50 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	check_lines(char **map, int l_nbr, t_tools el)
{
	el.i = 0;
	while (el.i < l_nbr - 1)
	{
		el.j = skip_whitespace(map[el.i]);
		if (map[el.i][el.j] == 'N' && map[el.i][el.j + 1] == 'O'
			&& map[el.i][el.j + 2] == ' ')
			el.i++;
		else if (map[el.i][el.j] == 'S' && map[el.i][el.j + 1] == 'O'
			&& map[el.i][el.j + 2] == ' ')
			el.i++;
		else if (map[el.i][el.j] == 'W' && map[el.i][el.j + 1] == 'E'
			&& map[el.i][el.j + 2] == ' ')
			el.i++;
		else if (map[el.i][el.j] == 'E' && map[el.i][el.j + 1] == 'A'
			&& map[el.i][el.j + 2] == ' ')
			el.i++;
		else if (map[el.i][el.j] == 'F' && map[el.i][el.j + 1] == ' ')
			el.i++;
		else if (map[el.i][el.j] == 'C' && map[el.i][el.j + 1] == ' ')
			el.i++;
		else if (!map[el.i][el.j])
			el.i++;
		else
			ft_error("Map is not valid, Invalid direction !");
	}
}

int	check_path(char *path)
{
	int	i;

	i = skip_whitespace(path) + 2 ;
	while (path[i])
	{
		if ((path[i] == '.' && path[i + 1] == '/') || path[i] == '/'
			|| ft_isalnum(path[i]))
			return (i);
		i++;
	}
	return (-1);
}

void	check_previous(int now, char *previous, char *next)
{
	int	prev_len;
	int	next_len;

	next_len = (int)ft_strlen(next);
	prev_len = (int)ft_strlen(previous);
	if (now > prev_len || now > next_len)
	{
		ft_error("Map is not valid, length problem !\n");
	}
}

int	check_extrm(char **map, int i, int j)
{
	int	k;

	k = 0;
	while (map[k])
		k++;
	if ((i == 0 || j == 0) || j == (int)ft_strlen(map[i]) - 1 || i == k - 1)
		return (1);
	return (0);
}

void	check_directions(char **map)
{
	int		i;
	int		j;
	char	*components;

	components = "01WESN";
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0' || map[i][j] == 'W' || map[i][j] == 'E'
				|| map[i][j] == 'S' || map[i][j] == 'N')
			{
				if (check_extrm(map, i, j))
					ft_error("Map is not valid, walls problem !\n");
				check_previous(j, map[i - 1], map[i + 1]);
				if (!ft_strchr(components, map[i - 1][j])
					|| !ft_strchr(components, map[i + 1][j]) \
					|| !ft_strchr(components, map[i][j - 1]) \
					|| !ft_strchr(components, map[i][j + 1]))
					ft_error("Map is not valid, check it again !\n");
			}
		}
	}
}
