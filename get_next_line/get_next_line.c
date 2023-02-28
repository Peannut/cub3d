/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:32:58 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/02/28 18:40:30 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include"get_next_line.h"

void	ft_check_endl(char **next, char **line)
{
	char	*c;
	char	*tmp;

	c = NULL;
	tmp = *next;
	if (*next)
	{
		c = ft_strchr(*next, '\n');
		if (c)
		{
			*next = ft_strdup(++c);
			c[0] = '\0';
			if (!(*next[0]))
				ft_free_it(next);
			*line = ft_strdup(tmp);
			ft_free_it(&tmp);
		}
		else
		{
			*line = ft_strdup(*next);
			ft_free_it(next);
		}
	}
}

void	ft_next_line(char **next, char *ptr)
{
	if (*ptr != '\0')
	{
		if (*next)
		{
			ft_free_it(next);
		}
		*next = ft_strdup(ptr);
	}
}

void	ft_write_line(char **line, char *buff)
{
	char	*tmp;
	char	*ok;

	tmp = *line;
	ok = NULL;
	if (!(*line))
	{	
		*line = ft_strdup("");
		ok = *line;
	}
	*line = ft_strjoin(*line, buff);
	if (ok)
		ft_free_it(&ok);
	if (tmp)
		ft_free_it(&tmp);
}

void	ft_check_buff(char **buff, char **next)
{
	char	*ptr;

	ptr = ft_strchr(*buff, '\n');
	if (ptr)
	{	
		ft_next_line(next, ++ptr);
		ptr[0] = '\0';
	}
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*next;
	char		*line;
	int			read_byte;
	int			buffer;

	buffer = 100;
	if (fd < 0 || buffer <= 0 || read(fd, 0, 0))
		return (NULL);
	buff = malloc(buffer + 1);
	read_byte = 1;
	line = NULL;
	buff[0] = 0;
	ft_check_endl(&next, &line);
	while (!ft_strchr(line, '\n'))
	{	
		read_byte = read(fd, buff, buffer);
		buff[read_byte] = '\0';
		if (read_byte == 0)
			break ;
		ft_check_buff(&buff, &next);
		ft_write_line(&line, buff);
	}
	ft_free_it(&buff);
	return (line);
}

