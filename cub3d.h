/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:59:54 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/18 00:59:36 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <math.h>
# include <mlx.h>


# define BLOCK 32
# define PI 3.1415926535
# define FOV_ANGEL 60 * (PI / 180)
# define WALL_STRIP_WIDTH 30
# define WIN_HEIGHT 720
# define WIN_WIDTH 1280
// fov angel in radiant btw :)

// typedef struct s_data
// {
// 	void *mlx;
// 	void *win;
// 	char **map;
// 	int	floor_color;
// 	int	ceiling_color;

// }t_datad;

typedef struct s_texture
{
	char	*info;
	char	*path;
	void	*img;
	int		width;
	int		height;
	
} t_texture;
typedef struct s_player
{
	double	x;
	double	y;
	double	rotationAngle;
	int sidewaysDirection; // -1 for left ,+1 for right
	int	turnDirection; // -1 for left, +1 for right
	int	walkDirection; // -1 for back, +1 for front
	double	moveSpeed; // the constant value is in squares/second
	double	rotationSpeed; // the constant value is in radians/second
	char spawn;
}	t_player;
typedef struct infos
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			*f;
	int			*c;
	char		**map;
	// int			x;
	// int			y;
}	t_info;

typedef struct data {
    //char **map;
	// t_texture	no_t;
	// t_texture	so_t;
	// t_texture	we_t;
	// t_texture	ea_t;
	// int			*floor_color;
	// int			*ceilling_color;
	void *mlx;
	void *mlx_win;
	void *frame;
	int	height;
	int	width;
	t_info *info;
    t_player player;
	t_texture img;
} t_data;

typedef struct	s_data {
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;


typedef struct s_tools
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
	int	counter;
	int	i;
	int	j;
}			t_tools;


typedef struct s_color
{
	char	*tmp;
	char	**hold;
	char	**hold2;
	int		*rgb;
	// float	distencetowall;
	// float	wallhight;
	// float	startp;
	// float	endp;
	// float	correct_ray_des;
	// char	*dst;
	// int		t_offsetx;
	// int		t_offsety;
	int		i;
} t_color;

// typedef struct s_player_params{
//     t_player *player;
//     char (*map)[10];
// } t_player_params;

void	init_the_map(char *map_name);
void	ft_error(char *msg);
void    exitfunc(void);

/************drawing*******/
void my_pixel_put(void *img, int x, int y, int color);
char **allocate_map(char **map, int i);
void draw_map(t_data *data);
void draw_grid(t_data *data);
void draw_player(t_data *data, int flag);
void draw_line(t_data *data);


/********update*******/
void update(t_data *data);
void render(t_data *data);

/*********data reader*********/
t_info	*ft_parse(char **av, t_data *data);
int		countlines(char *file);
int		countwidth(char *file);


/*****rays casting******/
void castAllRays(t_data *data);
void exitfunc(void);
#endif 
