/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:15:00 by abouhaga          #+#    #+#             */
/*   Updated: 2023/03/27 16:48:31 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

int	scan_line(char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (ft_isalnum(map[i]))
			return (1);
		i++;
	}
	return (0);
}

int	is_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' \
		&& line[i] != '\v' && line[i] != '\f' && line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

int	skip_whitespace(char *s)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (s[i] && !ft_isalnum(s[i]))
	{
		if (s[i] == ' ' || s[i] == '\t')
			c++;
		i++;
	}
	return (c);
}

char	*end_spaces(char *s)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = ft_strdup("");
	i = ft_strlen(s) - 1;
	j = 0;
	while (j < i)
	{
		if (s[i] == ' ')
			i--;
		else
			break ;
		j++;
	}
	j = 0;
	while (j <= i)
		tmp = ft_strjoin2c(tmp, s[j++]);
	free(s);
	return (tmp);
}
