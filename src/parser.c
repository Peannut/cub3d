/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:28:43 by abouhaga          #+#    #+#             */
/*   Updated: 2023/02/25 21:43:50 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_extension(char *map_file)
{
	char	*occurrence;

	occurrence = ft_strrchr(map_file, '.');
	if (!occurrence || ft_strcmp(occurrence, ".cub"))
		ft_error("map should have .cub extension");
}

//Set-up the player's position
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

void	check_previous(int now, char *previous, char *next)
{
	int	j;
	int	i;

	i = (int)ft_strlen(next);
	j = (int)ft_strlen(previous);
	if (now > j || now > i)
		ft_error("Map is not valid\n");
}

int	check_extrm(char **map, int i, int j)
{
	int	k;

	k = 0;
	while (map[k])
		k++;
	if ((i == 0 || j == 0) || j == (int)ft_strlen(map[i]) - 1 || i == k - 1)
		return (1);
	return (0);
}

void	valid_walls(char **map)
{
	int		i;
	int		j;
	char	*components;

	components = "01WESN";
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0' || map[i][j] == 'W' || map[i][j] == 'E'
				|| map[i][j] == 'S' || map[i][j] == 'N')
			{
				if (check_extrm(map, i, j))
					ft_error("Map is not valid\n");
				check_previous(j, map[i - 1], map[i + 1]);
				if (!ft_strchr(components, map[i - 1][j])
					|| !ft_strchr(components, map[i + 1][j]) \
					|| !ft_strchr(components, map[i][j - 1]) \
					|| !ft_strchr(components, map[i][j + 1]))
					ft_error("Map is not valid\n");
			}
		}
	}
}

//to ensure that the walls of the map are valid
//and that they surround the playable area.
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
            j++;
        }
        i++;
    }
    if (data->player.spawn == '+')
        ft_error("This Map has no player !");
    valid_walls(data->map);
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

// void add_line2map(char *line, t_data *data)
// {
    
// }
// void    load_files(int fd, t_data* data)
// {
//     char    *line;

//     while(1)
//     {
//         line = get_next_line(fd);
// 		if(!line)
// 			break;
//         if (check_init(data) && !is_spaces(line))
//             ft_extract_data(line, data);
//         else
//         {
//             if (is_spaces(line) && data->map)
//                 ft_error("Map is not valid");
//             else if (!is_spaces(line))
//                 add_line2map(line, data);
//         }
//         free(line);
//     }
//     if (!data->map || check_init(data))
//         ft_error("Map is not valid");
// }

void initialize(t_info *info)
{
    info->no = NULL;
    info->so = NULL;
    info->we = NULL;
    info->ea = NULL;
    info->f = NULL;
    info->c = NULL;
}

char *read_file(char* file)
{
    char *line;
    int fd;
    char *tmp;

    fd = open(file, O_RDONLY);
    line = ft_strdup("");
    if (fd < 0)
        ft_error("Couldn't open !");
    tmp = ft_strdup("");
    while(tmp)
    {
        free(tmp);
        tmp = get_next_line(fd);
        if (!tmp)
            break;
        if (!ft_strcmp("\n", tmp))
        {
            free(tmp);
            tmp = ft_strdup("\n");
        }
        line = ft_strjoin2(line, tmp);
    }
    free(tmp);
    return (line);
}

t_tools	initialize_tools()
{
	t_tools	tool;

	tool.no = 0;
	tool.so = 0;
	tool.we = 0;
	tool.ea = 0;
	tool.f = 0;
	tool.c = 0;
	return (tool);
}

int	scan_line(char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (ft_isalnum(map[i]))
			return (1);
		i++;
	}
	return (0);
}

 void check_lines(char **map, int l_nbr, t_tools tools)
 {
    tools.i = 0;
    while(tools.i < l_nbr - 1)
    {
        //continue here
        
    }
 }
int ft_scan_map(char **map, t_info *info)
{ 
    int j;
    int cnt;
    t_tools tools;

    i = 0;
    cnt = 0;
    tools = initialize_tools();
    tools.counter = 0;
    while(map[i])
    {
        if (!scan_line(map[i]))
            cnt++;
        else if (scan_line(map[i]) && tools.counter == 6)
            break;
        tools.counter = ft_extract_data(&tools, info, map, i);
            i++;
    }
    if (tools.counter != 6)
        ft_error("Map is not valid");
    check_lines(map, tools.counter + cnt, tools);
    return (cnt + tools.counter);
}

char	**readingdata(char *file, t_data *data)
{
    int fd;
    t_info *info;
    char *lines;
    char **map;
    int cnt;
	
    info = malloc(sizeof(t_info));
    initialize(info);
	check_extension(file); //if dir check 
    lines = read_file(file);
    map = ft_split(lines, '\n');
    free (lines);
    cnt = ft_scan_map(map, info);
    //load_files(fd, data);
	valid_map(data);
    return (map);
}