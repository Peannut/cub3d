/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:28:43 by abouhaga          #+#    #+#             */
/*   Updated: 2023/02/21 13:38:37 by abouhaga         ###   ########.fr       */
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
        data->map[i][j] = '0';
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

void    valid_walls(t_data *data)
{
    int i;
    int j;
    int k;

    i = 0;
    while(data->map[i])
    {
        j = 0;
        while(data->map[i][j])
        {
            k = data->map[i][j];
            if (k == 'S' || k == 'W' || k == 'N' || k == 'E' || k == '0')
                if (check_col(data, i, j) || check_row(data, i, j))
                    ft_error("Invalid Map walls !");
            j++;
        }
        i++;
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

void    load_files(int fd, t_data* data)
{
    char    *line;

    while(1)
    {
        line = get_next_line(fd);
		if(!line)
			break;
        
        
    }
    
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