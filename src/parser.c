/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:28:43 by abouhaga          #+#    #+#             */
/*   Updated: 2023/02/18 05:08:03 by abouhaga         ###   ########.fr       */
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
        if(data->player.spawn = '+')
            ft_error("More than one player");
        data->player.x = j;
        data->player.y = i;
        data->player.spawn = data->map[i][j];
        //map[i][j] ?
    }
    return (0);
}

int check_col(t_data *data, int i, int j)
{
    // check
    
}

void    valid_walls(t_data *data)
{
    int i;
    int j;
    int pos;

    i = 0;
    while(data->map[i])
    {
        j = 0;
        while(data->map[i][j])
        {
            pos = data->map[i][j];
            if (pos == 'S' || pos == 'W' || pos == 'N' || pos == 'E' || pos == '0')
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
            if(is_valid_component( data->map[i][j], data, i, j))
                ft_error("Map is not valid");
            j++
        }
        i++;
    }
    if (data->player.spawn == '+')
        ft_error("This Map has no player !");
    valid_walls(data);
}

char	**readingdata(char *file, t_data *data)
{
    int fd;
	
	check_extension(file, ".cub"); //if dir check 
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error("Map open : Failed !");
	valid_map(data);
}