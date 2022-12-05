/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:59:56 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/12/05 22:18:11 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minilibx-linux/mlx.h"

int main(int ac, char **av)
{
//    if (ac != 2)
//         ft_error("usage : ./cub3d map.cub");
//     init_the_map(av[1]);
    void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 600, 450, "Hello world!");
	mlx_loop(mlx);
    return (0);
}