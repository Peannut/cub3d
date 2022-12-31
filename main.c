/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:59:56 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/12/31 02:26:46 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include "cub3d.h"


// void render(void *mlx, void *window, char map[10][10], int screen_width, int screen_height) {
//     int x, y, i, j;
//     int color;

//     for (y = 0; y < 10; y++) {
//         for (x = 0; x < 10; x++) {
//             if (map[y][x] == '1') {
//                 color = 0xA020F0; 
//             } else {
//                 color = 0xFFFF00; 
//             }
//             for (i = 0; i < 32; i++) {
//                 for (j = 0; j < 32; j++) {
//                     mlx_pixel_put(mlx, window, x * 32 + i, y * 32 + j, color);
//                 }
//             }
//         }
//     }
// }
void render(void *mlx, void *window, char map[10][10], int screen_width, int screen_height) {
    int x, y, i, j;
    int color;

    for (y = 0; y < 10; y++) {
        for (x = 0; x < 10; x++) {
            if (map[y][x] == '1') {
                color = 0xA020F0; 
            } else {
                color = 0xFFFF00; 
            }
            for (i = 0; i < 32; i++) {
                for (j = 0; j < 32; j++) {
                    mlx_pixel_put(mlx, window, x * 32 + i, y * 32 + j, color);
                }
            }
            // draw grid
            for (i = 0; i < 32; i++) {
                mlx_pixel_put(mlx, window, x * 32 + i, y * 32 + 31, 0x000000);
            }
            for (j = 0; j < 32; j++) {
                mlx_pixel_put(mlx, window, x * 32 + 31, y * 32 + j, 0x000000);
            }
        }
    }
}

int main(int ac, char **av)
{
	//test2
//    if (ac != 2)
//         ft_error("usage : 1/cub3d map1cub");
//     init_the_map(av[1]);
    void	*mlx;
	void	*mlx_win;

	// 2d array map girder
	char map[10][10] = {
    {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '1', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
	};
	
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 320, 320, "Hello world!");
	render(mlx, mlx_win, map, 10, 10);
	mlx_loop(mlx);
    return (0);
}