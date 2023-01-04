/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:05:01 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/01/04 14:18:58 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**readingdata(char *file)
{
	char	**map;
	int		nblines;
	int		fd;
	int		i;
	char	*tmp;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 1)
	{
		printf("failed to open file\n");
		// possible leak hna knti dayr ft_erro 3ndak tnsa;
	}
	nblines = countlines(file);
	map = malloc(sizeof(char *) * (nblines + 1));
	while (1)
	{
		map[i] = get_next_line(fd);
		if (!map[i++])
			break ;
	}
	tmp = map[i - 2];
	map[i - 2] = ft_strjoin(map[i - 2], "\n");
	free(tmp);
	close(fd);
	return (map);
}

int	countlines(char *file)
{
	int		fd;
	char	*line;
	int		lines;

	lines = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("failed to open file");
		// same as her care"
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		lines++;
	}
	close(fd);
	return (lines);
}

int countwidth(char *file)
{
	int		fd;
	char	*line;
	int		width;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("failed to open file");
		// same as her care"
	}
	line = get_next_line(fd);
	width = ft_strlen(line);
	free(line);
	close(fd);
	return (width);
}