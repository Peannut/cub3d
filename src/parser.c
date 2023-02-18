/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:28:43 by abouhaga          #+#    #+#             */
/*   Updated: 2023/02/18 03:03:37 by abouhaga         ###   ########.fr       */
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

int is_valid(char ch, t_data *data, int i, int j)
{
    if (ch != '1' && ch != '0' && ch != ' ' && ch != 'E'
            && ch != 'N' && ch != 'W' && ch != 'S')
        return (1);
    if (ch == 'N' || ch == 'S' || ch == 'W' || ch == 'E')
    {
        //check more than one player here

        data->player.x = j;
        data->player.y = i;
        data->player.dir = ch;
        //pos ??
    }
    return (0);
}

void    valid_map(t_data *data)
{
    int i;
    int j;

    i = 0;
    while(data->map[i])
    {
        j = 0;
        while(data->map[i][j])
        {
            if(is_valid( data->map[i][j], data, i, j))
                ft_error("Map is not valid");
            j++
        }
        i++;
    }
    //player
    valid_walls(data);
}

char	**readingdata(char *file, t_data *data)
{
    int fd;
	
	check_extension(file, ".cub"); //if dir check 
	fd = open(file, O_RDONLY);
	if (fd < 1)
		ft_error("Map open : Failed !");
	valid_map(data);
}