/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:28:43 by abouhaga          #+#    #+#             */
/*   Updated: 2023/03/22 14:01:28 by zoukaddo         ###   ########.fr       */
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
        data->player.x = j * BLOCK + BLOCK / 2 + 1;
        data->player.y = i * BLOCK + BLOCK / 2 + 1;
        data->player.spawn = data->info->map[i][j];
        printf("spawn in pars %c\n", data->player.spawn);
		//data->map[i][j] = '0';
    }
    return (0);
}

void check_previous(int now, char *previous, char *next)
{
    int prev_len = (int)ft_strlen(previous);
    int next_len = (int)ft_strlen(next);
    
    if (now > prev_len || now > next_len) {
        ft_error("Map is not valid, length problem !\n");
    }
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
    info->no = 0;
    info->so = 0;
    info->we = 0;
    info->ea = 0;
    info->f = 0;
    info->c = 0;
}

char *read_file(char** av, t_info *info)
{
    char *line;
    int fd;
    char *tmp;

	(void)info;
    line = ft_strdup("");
    fd = open(av[1], O_RDONLY);
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

void check_lines(char **map, int l_nbr, t_tools el)
{
    el.i = 0;
    while(el.i < l_nbr - 1)
    {
        el.j = skip_whitespace(map[el.i]);
        if (map[el.i][el.j] == 'N' && map[el.i][el.j + 1] == 'O'
            && map[el.i][el.j + 2] == ' ')
            el.i++;
        else if (map[el.i][el.j] == 'S' && map[el.i][el.j + 1] == 'O'
            && map[el.i][el.j + 2] == ' ')
            el.i++;
        else if (map[el.i][el.j] == 'W' && map[el.i][el.j + 1] == 'E'
            && map[el.i][el.j + 2] == ' ')
            el.i++;
        else if (map[el.i][el.j] == 'E' && map[el.i][el.j + 1] == 'A'
            && map[el.i][el.j + 2] == ' ')
            el.i++;
        else if (map[el.i][el.j] == 'F' && map[el.i][el.j + 1] == ' ')
            el.i++;
        else if (map[el.i][el.j] == 'C' && map[el.i][el.j + 1] == ' ')
            el.i++;
		else if (!map[el.i][el.j])
			el.i++;
        else
            ft_error("Map is not valid, Invalid direction !");   
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
		ft_error("invalid north path !\n");
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
		ft_error("invalid south path !\n");
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
		ft_error("invalid east path !\n");
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
		ft_error("invalid west path !\n");
	while (map[cnt])
		tmp = ft_strjoin2c(tmp, map[cnt++]);
	tmp = end_spaces(tmp);
	if (!info->we)
		info->we = tmp;
	else
		free(tmp);
}

int	valid_rgb_help(char *s)
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
		ft_error("Invalid RGB, out of range !\n");
}

int	*valid_rgb(t_color *color)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = 0;
	while (color->arr[++i])
	{
		color->hold2 = ft_split(color->arr[i], ' ');
		k = 0;
		while (color->hold2[k])
			k++;
		if (k > 1)
			ft_error("Invalid RGB\n");
		if (j < 3)
		{ 
			if (valid_rgb_help(color->arr[i]))
				ft_error("Invalid RGB\n");
			color->rgb[j] = ft_atoi(color->arr[i]);
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
	clr.arr = ft_split(clr.tmp, ',');
	clr.i = 0;
	while (clr.arr[clr.i])
		clr.i++;
	if (clr.i != 3)
		ft_error("Invalid RGB\n");
	clr.rgb = valid_rgb(&clr);
	free(clr.tmp);
	ft_free(clr.arr);
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
        ft_error("Map is not valid, extra info !");
    check_lines(map, tools.counter + cnt, tools);
    return (cnt + tools.counter);
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
				ft_error("dude verify yr map components!\n");
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
					ft_error("Map is not valid, walls problem !\n");
				check_previous(j, map[i - 1], map[i + 1]);
				if (!ft_strchr(components, map[i - 1][j])
					|| !ft_strchr(components, map[i + 1][j]) \
					|| !ft_strchr(components, map[i][j - 1]) \
					|| !ft_strchr(components, map[i][j + 1]))
					ft_error("Map is not valid, check it again !\n");
			}
		}
	}
}

void	valid_player(char **map, t_data *data)
{
	int	i;
	int	j;
	int	pos;

	pos = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'W'
				|| map[i][j] == 'S' || map[i][j] == 'E')
				{
					if (pos == 0)
					{
						data->player.spawn = map[i][j];
						data->player.x = i  * BLOCK * BLOCK / 2;
						data->player.y = j  * BLOCK * BLOCK / 2;
					}
					pos++;

				}
			j++;
		}
		i++;
	}
	if (pos != 1)
		ft_error("Map is not valid, Zero or multiple player positions !\n");
}

//to ensure that the walls of the map are valid
//and that they surround the playable area.
void setup_map(t_info *info, char **map, int cnt, t_data *data)
{
    char **tmp;

    tmp = allocate_map(map, cnt);
	// print_map(tmp);
    // exit(0);
	check_map_components(tmp);
	check_directions(tmp);
    valid_player(tmp, data);
    info->map = tmp;
}

void print_map(char **map)
{
    int i = 0;
    while (map[i] != NULL)
    {
        printf("%s\n", map[i]);
        i++;
    }
}

t_info	*ft_parse(char **av, t_data *data)
{
    t_info *info;
    char *lines;
    char **map;
    int cnt;
	
    info = malloc(sizeof(t_info));
    initialize(info);
	check_extension(av); //if dir check
    lines = read_file(av, info);
    map = ft_split(lines, '\n');
    free (lines);
    cnt = ft_scan_map(map, info);
    setup_map(info, map, cnt, data);
	print_map(info->map);
    ft_free(map);
    return (info);
}