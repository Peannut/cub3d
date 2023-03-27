/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsemap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:10:52 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/27 17:24:26 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_error(char *msg)
{
	ft_putendl_fd("Error :", 2);
	ft_putendl_fd(msg, 2);
	exit(1);
}

void	format_check(char *map_name, char *format)
{
	char	*str;

	str = ft_strrchr(map_name, '.');
	if (!str || ft_strcmp(str, format))
	{
		if (!ft_strcmp(format, ".cub"))
			ft_error("the map should be .cub format");
	}
}

void	readmap(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
	}
}

void	init_the_map(char *map_name)
{
	int	fd;

	format_check(map_name, ".cub");
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		ft_error("open the map failed");
	readmap(fd);
}
