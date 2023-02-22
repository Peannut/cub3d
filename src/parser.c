/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:28:43 by abouhaga          #+#    #+#             */
/*   Updated: 2023/02/22 22:04:06 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_extension(char *map_file, char *ext)
{
	char	*occurrence;

	occurrence = ft_strrchr(map_file, '.');
	if (!occurrence || ft_strcmp(occurrence, ext))
		ft_error("map should have .cub extension");
}

int is_valid_component(char ch, t_data *data, int i, int j)
{
    if (ch != '1' && ch != '0' && ch != ' ' && ch != 'E'
            && ch != 'N' && ch != 'W' && ch != 'S')
        return (1);
    if (ch == 'N' || ch == 'S' || ch == 'W' || ch == 'E')
    {
        if(data->player.spawn != '+')
            ft_error("More than one player");
        data->player.x = j;
        data->player.y = i;
        data->player.spawn = data->map[i][j];
        //data->map[i][j] = '0';
    }
    return (0);
}

int check_row(t_data *data, int i, int j)
{
    int tmp_row;

    tmp_row = i;

    while (data->map[i])
    {
        if (data->map[i][j] == ' ' || j >= ft_strlen(data->map[i]))
            return (1);
        if (data->map[i][j] == '1')
            break;
        i++;
    }
    if (!data->map[i])
        return (1);
    while (tmp_row >= 0)
    {
        if (data->map[tmp_row][j] == ' ' || j >= ft_strlen(data->map[tmp_row]))
            return (1);
        if (data->map[tmp_row][j] == '1')
            break;
        tmp_row--;
    }
    if (tmp_row < 0)
        return (1);
    return (0); 
}

int check_col(t_data *data, int i, int j)
{
    int tmp_col;

    tmp_col = j;
    while (data->map[i][j])
    {
        if (data->map[i][j] == ' ')
            return (1);
        if (data->map[i][j] == '1')
            break;
        j++;
    }
    if (!data->map[i][j])
        return (1);
    while (tmp_col >= 0)
    {
        if (data->map[i][tmp_col] == ' ')
            return (1);
        if (data->map[i][tmp_col] == '1')
            break;
        tmp_col--;
    }
    if (tmp_col < 0)
        return (1);
    return (0); 
}

void	valid_walls(char **mapv)
{
	int		j;
	int		i;
	char	*elements;

	elements = "01WESN";
	i = -1;
	while (mapv[++i])
	{
		j = -1;
		while (mapv[i][++j])
		{
			if (mapv[i][j] == '0' || mapv[i][j] == 'W' || mapv[i][j] == 'E'
				|| mapv[i][j] == 'S' || mapv[i][j] == 'N')
			{
				if (check_edges(mapv, i, j))
					print_error("ERROR\n");
				check_previous(j, mapv[i - 1], mapv[i + 1]);
				if (!ft_strchr(elements, mapv[i - 1][j])
					|| !ft_strchr(elements, mapv[i + 1][j]) \
					|| !ft_strchr(elements, mapv[i][j - 1]) \
					|| !ft_strchr(elements, mapv[i][j + 1]))
					print_error("ERROR\n");
			}
		}
	}
}

void    valid_map(t_data *data)
{
    int i;
    int j;

    i = 0;
    data->player.spawn = '+';
    while(data->map[i])
    {
        j = 0;
        while(data->map[i][j])
        {
            if (is_valid_component(data->map[i][j], data, i, j))
                ft_error("Map is not valid");
            j++
        }
        i++;
    }
    if (data->player.spawn == '+')
        ft_error("This Map has no player !");
    valid_walls(data);
}

int check_init(t_data *data)
{
    if (data->ea_t.img == NULL || data->no_t.img == NULL \
	|| data->so_t.img == NULL || data->we_t.img == NULL \
	|| data->floor_color == NULL || data->ceilling_color == NULL)
		return (1);
	else
		return (0);
}

int is_spaces(char *line)
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

void add_line2map(char *line, t_data *data)
{
    
}
void    load_files(int fd, t_data* data)
{
    char    *line;

    while(1)
    {
        line = get_next_line(fd);
		if(!line)
			break;
        if (check_init(data) && !is_spaces(line))
            ft_extract_data(line, data);
        else
        {
            if (is_spaces(line) && data->map)
                ft_error("Map is not valid");
            else if (!is_spaces(line))
                add_line2map(line, data);
        }
        free(line);
    }
    if (!data->map || check_init(data))
        ft_error("Map is not valid");
}
char	**readingdata(char *file, t_data *data)
{
    int fd;
	
    data->ea_t.texture = NULL;
    data->no_t.texture = NULL;
    data->so_t.texture = NULL;
    data->we_t.texture = NULL;
    data->map = NULL;
	check_extension(file, ".cub"); //if dir check 
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error("Map open : Failed !");
    load_files(fd, data);
	valid_map(data);
}