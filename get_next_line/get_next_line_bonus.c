/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:15:11 by zoukaddo          #+#    #+#             */
/*   Updated: 2021/12/02 14:06:54 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
				ft_free(next);
			*line = ft_strdup(tmp);
			ft_free(&tmp);
		}
		else
		{
			*line = ft_strdup(*next);
			ft_free(next);
		}
	}
}

void	ft_next_line(char **next, char *ptr)
{
	if (*ptr != '\0')
	{
		if (*next)
		{
			ft_free(next);
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
		ft_free(&ok);
	if (tmp)
		ft_free(&tmp);
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
	static char	*next[OPEN_MAX];
	char		*line;
	int			read_byte;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0))
		return (NULL);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	line = NULL;
	ft_check_endl(&next[fd], &line);
	while (!ft_strchr(line, '\n'))
	{	
		read_byte = read(fd, buff, BUFFER_SIZE);
		if (read_byte == -1)
			return (NULL);
		buff[read_byte] = '\0';
		if (read_byte == 0)
			break ;
		ft_check_buff(&buff, &next[fd]);
		ft_write_line(&line, buff);
	}
	ft_free(&buff);
	return (line);
}
