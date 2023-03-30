/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:28:43 by abouhaga          #+#    #+#             */
/*   Updated: 2023/03/30 21:44:27 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	check_extension(char **map_file)
{
	char	*occurrence;

	occurrence = ft_strrchr(map_file[1], '.');
	if (!occurrence || ft_strcmp(occurrence, ".cub"))
		ft_error("map should have .cub extension");
}

//to ensure that the walls of the map are valid
//and that they surround the playable area.
void	setup_map(t_info *info, char **map, int cnt, t_data *data)
{
	char	**tmp;

	tmp = allocate_map(map, cnt);
	check_map_components(tmp);
	check_directions(tmp);
	valid_player(tmp, data);
	info->map = tmp;
}

char	*read_file(char **av, t_info *info)
{
	char	*line;
	int		fd;
	char	*tmp;

	(void)info;
	line = ft_strdup("");
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		ft_error("Couldn't open !");
	tmp = ft_strdup("");
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
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

int	ft_scan_map(char **map, t_info *info)
{
	int		i;
	int		cnt;
	t_tools	tools;

	i = 0;
	cnt = 0;
	tools = initialize_tools();
	tools.counter = 0;
	while (map[i])
	{
		if (!scan_line(map[i]))
			cnt++;
		else if (scan_line(map[i]) && tools.counter == 6)
			break ;
		tools.counter = ft_extract_data(&tools, info, map, i);
		i++;
	}
	if (tools.counter != 6)
		ft_error("Map is not valid, extra info !");
	check_lines(map, tools.counter + cnt, tools);
	return (cnt + tools.counter);
}

t_info	*ft_parse(char **av, t_data *data)
{
	t_info	*info;
	char	*lines;
	char	**map;
	int		cnt;

	info = malloc(sizeof(t_info));
	initialize(info);
	check_extension(av);
	lines = read_file(av, info);
	map = ft_split(lines, '\n');
	free (lines);
	cnt = ft_scan_map(map, info);
	setup_map(info, map, cnt, data);
	ft_free(map);
	return (info);
}
