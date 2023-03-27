/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:05:01 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/27 17:05:56 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

int	countwidth(char *file)
{
	int		fd;
	char	*line;
	int		width;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		printf("failed to open file");
	line = get_next_line(fd);
	width = ft_strlen(line);
	free(line);
	close(fd);
	return (width);
}
