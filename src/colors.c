/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:09:03 by abouhaga          #+#    #+#             */
/*   Updated: 2023/04/01 00:07:17 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	valid_rgb_help(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (1);
		i++;
	}
	return (0);
}

void	rgb_handling(int rgb)
{
	if (rgb < 0 || rgb > 255)
		ft_error("Invalid RGB, out of range !\n");
}

int	*valid_rgb(t_color *color)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = 0;
	while (color->arr[++i])
	{
		color->hold2 = ft_split(color->arr[i], ' ');
		k = 0;
		while (color->hold2[k])
			k++;
		if (k > 1)
			ft_error("Invalid RGB\n");
		if (j < 3)
		{
			if (valid_rgb_help(color->arr[i]))
				ft_error("Invalid RGB\n");
			color->rgb[j] = ft_atoi(color->arr[i]);
			rgb_handling(color->rgb[j]);
			j++;
		}
		ft_free(color->hold2);
	}
	return (color->rgb);
}

t_color	read_rgb_values(char *map, t_color clr)
{
	while (map[clr.i])
	{
		if (map[clr.i] == ',' && (map[clr.i + 1] == ',' || !map[clr.i + 1]))
			ft_error("Invalid RGB\n");
		clr.tmp = ft_strjoin2c(clr.tmp, map[clr.i++]);
	}
	clr.tmp = end_spaces(clr.tmp);
	clr.arr = ft_split(clr.tmp, ',');
	clr.i = 0;
	while (clr.arr[clr.i])
		clr.i++;
	if (clr.i != 3)
		ft_error("Invalid RGB\n");
	return (clr);
}

int	*ft_check_colors(char *map)
{
	t_color	clr;

	clr.rgb = malloc(sizeof(int) * 3);
	clr.tmp = ft_strdup("");
	clr.i = skip_whitespace(map) + 1;
	while (map[clr.i] && !ft_isdigit(map[clr.i]))
	{
		if (map[clr.i] == ',')
			ft_error("Invalid RGB\n");
		if (map[clr.i] == ' ' || map[clr.i] == '\t')
			clr.i++;
	}
	clr = read_rgb_values(map, clr);
	clr.rgb = valid_rgb(&clr);
	free(clr.tmp);
	ft_free(clr.arr);
	return (clr.rgb);
}
