/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:59:56 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/31 15:03:51 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"

int	ft_start(char **av, t_data *cube)
{
	cube->info = ft_parse(av, cube);
	return (0);
}

size_t	ptrline(char **str)
{
	size_t	length;

	length = 0;
	while (str[length])
		length++;
	return (length);
}

int	thebiggestlen(t_data *data)
{
	int	i;
	int	max;
	int	len;

	len = 0;
	i = 0;
	max = 0;
	while (i < data->height)
	{
		len = ft_strlen(data->info->map[i]);
		if (max < len)
			max = len;
		i++;
	}
	return (max);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
	{
		printf("usage : cub3d ./file.cub\n");
		exit(1);
	}
	ft_start(av, &data);
	init_rotationangel(&data);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d!");
	data.frame = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	draw_map(&data);
	draw_player(&data, 1);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.frame, 0, 0);
	render(&data);
	mlx_hook(data.mlx_win, 2, 0, key_press, &data);
	mlx_hook(data.mlx_win, 3, 0, key_release, &data);
	mlx_hook(data.mlx_win, 6, 0, mouse_event, &data);
	mlx_hook(data.mlx_win, 17, 0, exitfunc, &data);
	mlx_loop(data.mlx);
	return (0);
}
