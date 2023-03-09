/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:28:43 by abouhaga          #+#    #+#             */
/*   Updated: 2023/03/09 02:02:46 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_free(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		s[i] = 0;
		i++;
	}
	free(s);
	s = NULL;
}

void	check_extension(char **map_file)
{
	char	*occurrence;

	occurrence = ft_strrchr(map_file[1], '.');
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
        data->player.spawn = data->info->map[i][j];
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

// void    valid_map(char **map, t_data *data)
// {
//     int i;
//     int j;

//     i = 0;
//     data->player.spawn = '+';
// 	data->info->map = map;
//     while(data->info->map[i])
//     {
//         j = 0;
//         while(data->info->map[i][j])
//         {
//             if (is_valid_component(data->info->map[i][j], data, i, j))
//                 ft_error("Map is not valid");
//             j++;
//         }
//         i++;
//     }
//     if (data->player.spawn == '+')
//         ft_error("This Map has no player !");
//     valid_walls(data->info->map);
// }

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

void initialize(t_info *info)
{
    info->no = NULL;
    info->so = NULL;
    info->we = NULL;
    info->ea = NULL;
    info->f = NULL;
    info->c = NULL;
}

char *read_file(char** av)
{
    char *line;
    int fd;
    char *tmp;

    fd = open(av[1], O_RDONLY);
    line = ft_strdup("");
    if (fd == -1)
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
            tmp = ft_strdup(" \n");
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

int	skip_whitespace(char *s)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (s[i] && !ft_isalnum(s[i]))
	{
		if (s[i] == ' ' || s[i] == '\t')
			c++;
		i++;
	}
	return (c);
}

void check_lines(char **map, int l_nbr, t_tools tl)
{
    tl.i = 0;
    while(tl.i < l_nbr - 1)
    {
        tl.j = skip_whitespace(map[tl.i]);
        if (map[tl.i][tl.j] == 'N' && map[tl.i][tl.j + 1] == 'O'
            && map[tl.i][tl.j + 2] == ' ')
            tl.i++;
        else if (map[tl.i][tl.j] == 'S' && map[tl.i][tl.j + 1] == 'O'
            && map[tl.i][tl.j + 2] == ' ')
            tl.i++;
        else if (map[tl.i][tl.j] == 'W' && map[tl.i][tl.j + 1] == 'E'
            && map[tl.i][tl.j + 2] == ' ')
            tl.i++;
        else if (map[tl.i][tl.j] == 'E' && map[tl.i][tl.j + 1] == 'A'
            && map[tl.i][tl.j + 2] == ' ')
            tl.i++;
        else if (map[tl.i][tl.j] == 'F' && map[tl.i][tl.j + 1] == ' ')
            tl.i++;
        else if (map[tl.i][tl.j] == 'C' && map[tl.i][tl.j + 1] == ' ')
            tl.i++;
		else if (!map[tl.i][tl.j])
			tl.i++;
        else
            ft_error("Map is not valid");   
    }
}

int	check_path(char *path)
{
	int	i;

	i = skip_whitespace(path) + 2 ;
	while (path[i])
	{
		if ((path[i] == '.' && path[i + 1] == '/') || path[i] == '/'
			|| ft_isalnum(path[i]))
			return (i);
		i++;
	}
	return (-1);
}

char	*end_spaces(char *s)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = ft_strdup("");
	i = ft_strlen(s) - 1;
	j = 0;
	while (j < i)
	{
		if (s[i] == ' ')
			i--;
		else
			break ;
		j++;
	}
	j = 0;
	while (j <= i)
		tmp = ft_strjoin2c(tmp, s[j++]);
	free(s);
	return (tmp);
}

void	north(char *map, t_info *info)
{
	char	*tmp;
	int		i;
	int		cnt;

	i = 0;
	tmp = ft_strdup("");
	cnt = check_path(map);
	if (cnt == -1)
		ft_error("invalid north path dude !\n");
	while (map[cnt])
		tmp = ft_strjoin2c(tmp, map[cnt++]);
	tmp = end_spaces(tmp);
	if (!info->no)
		info->no = tmp;
	else
		free(tmp);
}

void	south(char *map, t_info *info)
{
	char	*tmp;
	int		i;
	int		cnt;

	i = 0;
	tmp = ft_strdup("");
	cnt = check_path(map);
	if (cnt == -1)
		ft_error("invalid south path dude !\n");
	while (map[cnt])
		tmp = ft_strjoin2c(tmp, map[cnt++]);
	tmp = end_spaces(tmp);
	if (!info->so)
		info->so = tmp;
	else
		free(tmp);
}

void	east(char *map, t_info *info)
{
	char	*tmp;
	int		i;
	int		cnt;

	i = 0;
	tmp = ft_strdup("");
	cnt = check_path(map);
	if (cnt == -1)
		ft_error("invalid south path dude !\n");
	while (map[cnt])
		tmp = ft_strjoin2c(tmp, map[cnt++]);
	tmp = end_spaces(tmp);
	if (!info->ea)
		info->ea = tmp;
	else
		free(tmp);
}

void	west(char *map, t_info *info)
{
	char	*tmp;
	int		i;
	int		cnt;

	i = 0;
	tmp = ft_strdup("");
	cnt = check_path(map);
	if (cnt == -1)
		ft_error("invalid path dude !\n");
	while (map[cnt])
		tmp = ft_strjoin2c(tmp, map[cnt++]);
	tmp = end_spaces(tmp);
	if (!info->we)
		info->we = tmp;
	else
		free(tmp);
}

int	valid_rgb(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (1);
		i++;
	}
	return (0);
}

void	rgb_handling(int rgb)
{
	if (rgb < 0 || rgb > 255)
		ft_error("Invalid RGB\n");
}

int	*rgb_check_help(t_color *color)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = 0;
	while (color->hold[++i])
	{
		color->hold2 = ft_split(color->hold[i], ' ');
		k = 0;
		while (color->hold2[k])
			k++;
		if (k > 1)
			ft_error("Invalid RGB\n");
		if (j < 3)
		{ 
			if (valid_rgb(color->hold[i]))
				ft_error("Invalid RGB\n");
			color->rgb[j] = ft_atoi(color->hold[i]);
			rgb_handling(color->rgb[j]);
			j++;
		}
		ft_free(color->hold2);
	}
	return (color->rgb);
}

int	*ft_check_colors(char *map)
{
	t_color	clr;

	clr.rgb = malloc(sizeof(int) * 3);
	clr.tmp = ft_strdup("");
	clr.i = skip_whitespace(map) + 1;
	while (map[clr.i] && !ft_isdigit(map[clr.i]))
	{
		if (map[clr.i] == ',')
			ft_error("Invalid RGB\n");
		if (map[clr.i] == ' ' || map[clr.i] == '\t')
			clr.i++;
	}
	while (map[clr.i])
		clr.tmp = ft_strjoin2c(clr.tmp, map[clr.i++]);
	clr.tmp = end_spaces(clr.tmp);
	clr.hold = ft_split(clr.tmp, ',');
	clr.i = 0;
	while (clr.hold[clr.i])
		clr.i++;
	if (clr.i != 3)
		ft_error("Invalid RGB\n");
	clr.rgb = rgb_check_help(&clr);
	free(clr.tmp);
	ft_free(clr.hold);
	return (clr.rgb);
}

void	ft_floor(char *map, t_info *info)
{
	if (!info->f)
		info->f = ft_check_colors(map);
}

void	ft_ceilling(char *map, t_info *info)
{
	if (!info->c)
		info->c = ft_check_colors(map);
} 

int	ft_extract_data(t_tools *tl, t_info *info, char **map, int i)
{
	int	j;

	j = skip_whitespace(map[i]);
	if (!tl->no && (map[i][j] == 'N'
		&& map[i][j + 1] == 'O' && map[i][j + 2] == ' '))
		(north(map[i], info), tl->counter++, tl->no = 1);
	else if (!tl->so && (map[i][j] == 'S'
		&& map[i][j + 1] == 'O' && map[i][j + 2] == ' '))
		(south(map[i], info), tl->counter++, tl->so = 1);
	else if (!tl->we && (map[i][j] == 'W'
		&& map[i][j + 1] == 'E' && map[i][j + 2] == ' '))
		(west(map[i], info), tl->counter++, tl->we = 1);
	else if (!tl->ea && (map[i][j] == 'E'
		&& map[i][j + 1] == 'A' && map[i][j + 2] == ' '))
		(east(map[i], info), tl->counter++, tl->ea = 1);
	else if (!tl->f && (map[i][j] == 'F' && map[i][j + 1] == ' '))
		(ft_floor(map[i], info), tl->counter++, tl->f = 1);
	else if (!tl->c && (map[i][j] == 'C' && map[i][j + 1] == ' '))
		(ft_ceilling(map[i], info), tl->counter++, tl->c = 1);
	return (tl->counter);
}

int ft_scan_map(char **map, t_info *info)
{ 
    int i;
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

char **allocate(char **map, int cnt)
{
    int i;
    int j;
    char **tmp;
    
    i = cnt;
    j = 0;
    while(map[i])
        i++, j++;
    tmp = malloc(sizeof(char *) * (j + 1));
    j = 0;
    while (map[cnt])
        tmp[j++] = ft_strdup(map[cnt++]);
    tmp[j] = NULL;
    return (tmp);
}

void	check_map_components(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'W'
				&& map[i][j] != 'E' && map[i][j] != 'S' && map[i][j] != 'N' \
				&& map[i][j] != ' ')
				ft_error("dude verify yr map!\n");
			j++;
		}
		i++;
	}
}

void	check_directions(char **map)
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

void	valid_player(char **map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'W'
				|| map[i][j] == 'S' || map[i][j] == 'E')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		ft_error("ERROR\n");
}

//to ensure that the walls of the map are valid
//and that they surround the playable area.
void setup_map(t_info *info, char **map, int cnt, t_data *data)
{
    char **tmp;

    tmp = allocate(map, cnt);
	check_map_components(tmp);
	check_directions(tmp);
    valid_player(tmp);
    info->map = tmp;
}

t_info	*ft_parse(char **av, t_data *data)
{
    int fd;
    t_info *info;
    char *lines;
    char **map;
    int cnt;
	
    info = malloc(sizeof(t_info));
    initialize(info);
	check_extension(av); //if dir check
	// fd = open(av[1], O_RDONLY);
	// if (fd < 0)
	// 	ft_error("Couldn't open !");
    lines = read_file(av);
    map = ft_split(lines, '\n');
    free (lines);
    cnt = ft_scan_map(map, info);
    //load_files(fd, data);
    setup_map(info, map, cnt, data);
    ft_free(map);
    return (info);
}