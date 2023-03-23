/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:59:54 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/22 14:50:31 by zoukaddo         ###   ########.fr       */
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
# include <stdbool.h>


# define BLOCK 32
# define PI 3.1415926535
# define FOV_ANGEL 60 * (PI / 180)
# define WALL_STRIP_WIDTH 30
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define MINIMAP_SCALE 0.2
// fov angel in radiant btw :)
typedef struct  s_ray
{
    double	rayAngle;
    double	x;
    double	y;
    double	distance;
    bool	HitVertical;
	bool	HitHorizontal;
    int		rayFacingDown;
    int		rayFacingUp;
    int		rayFacingLeft;
    int		rayFacingRight;
	int		Hitx;
	int		Hity;
	int 	wallHeight;
}               t_ray;	

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
typedef struct infos
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			*f;
	int			*c;
	char		**map;
	t_tools		*tool;
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
	void *text;
	int	height;
	int	width;
	int raysnumba;
	t_ray	rays[WIN_WIDTH];
	t_info *info;
    t_player player;
	t_texture img;
} t_data;

typedef struct	s_img {
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;




typedef struct s_color
{
	char	*tmp;
	char	**arr;
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
typedef struct s_vec
{
	int x;
	int y;
} t_vec;

// typedef struct s_player_params{
//     t_player *player;
//     char (*map)[10];
// } t_player_params;

int count_lines(char **map);
int get_longest_line(char **map);
void print_map(char **map);
void	init_the_map(char *map_name);
void	ft_error(char *msg);
int    exitfunc(t_data *data);

/************drawing*******/
void my_pixel_put(void *img, int x, int y, int color);
char **allocate_map(char **map, int i);
void draw_map(t_data *data);
void draw_grid(t_data *data);
void draw_player(t_data *data, int flag);
void draw_line2(void *img, double x1, double y1, double x2, double y2, int color);

/********update*******/
void update(t_data *data);
void render(t_data *data);

/*********data reader*********/
t_info	*ft_parse(char **av, t_data *data);
int		countlines(char *file);
int		countwidth(char *file);


/*****rays casting******/
void castAllRays(t_data *data);


/******horiz and ver*****/
double	distancecalc(t_player first, t_vec sec);
double normalizeAngle(double angle);



/*********vert rays******/
// double vertical_rays(t_data *data, int ray);
t_vec	vertical_rays(t_data *data, int ray);
t_vec	horizontal_ray(t_data *data, int ray);
void	hitsave(t_data *data,bool val1 , bool val2,int ray);
void	findverticalsteps(t_data *data,t_vec *intercept, t_vec *step, int ray);
void	draw_ceiling_and_floor(t_data *data);
void	minimap_render(t_data *data);
void	render_ceiling(t_data *data, int x, int wallHeight);
void	render_floor(t_data *data, int x, int wallHeight);
/*************mouse***********/

int		mouse_event(int x, int y, void *data);
int		mlx_mouse_hide();
int		mlx_mouse_move(void *win_ptr, int x, int y);

#endif
