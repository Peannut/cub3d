/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:07:59 by abouhaga          #+#    #+#             */
/*   Updated: 2023/03/26 02:09:39 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
