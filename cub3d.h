/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:59:54 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/01/09 05:44:14 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
#include <math.h>


# define BLOCK 32
# define PI 3.1415926535
# define FOV_ANGEL 60 * (PI / 180)
// fov angel in radiant btw :)

// typedef struct s_data
// {
// 	void *mlx;
// 	void *win;
// 	char **map;
// 	int	floor_color;
// 	int	ceiling_color;

// }t_datad;


typedef struct s_player
{
	double	x;
	double	y;
	double	rotationAngle;
	int	turnDirection; // -1 for left, +1 for right
	int	walkDirection; // -1 for back, +1 for front
	double	moveSpeed; // the constant value is in squares/second
	double	rotationSpeed; // the constant value is in radians/second
}	t_player;

typedef struct data {
    char **map;
	void *mlx;
	void *mlx_win;
	int	height;
	int	width;
    t_player player;
} t_data;


// typedef struct s_player_params{
//     t_player *player;
//     char (*map)[10];
// } t_player_params;


void	init_the_map(char *map_name);
void	ft_error(char *msg);

/************drawing*******/
void draw_map(t_data *data);
void draw_grid(t_data *data);
void draw_player(t_data *data, int flag);
void draw_line(t_data *data);


/********update*******/
void update(t_data *data);
void render(t_data *data);

/*********data reader*********/
char	**readingdata(char *file);
int		countlines(char *file);
int countwidth(char *file);


/*****rays casting******/
void castAllRays(t_data *data);
#endif 
