/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:59:54 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/17 08:00:06 by zoukaddo         ###   ########.fr       */
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

typedef struct vector
{
	int x; 
	int y;
}	t_vec;

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
}	t_player;

typedef struct data {
    char **map;
	void *mlx;
	void *mlx_win;
	void *frame;
	void *text;
	int	height;
	int	width;
	int	raysnumba;
    t_player player;
	t_ray	rays[WIN_WIDTH];
} t_data;

typedef struct	s_img {
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;


void	init_the_map(char *map_name);
void	ft_error(char *msg);
void    exitfunc(void);

/************drawing*******/
void my_pixel_put(void *img, int x, int y, int color);
void draw_map(t_data *data);
void draw_grid(t_data *data);
void draw_player(t_data *data, int flag);
void draw_line2(void *img, double x1, double y1, double x2, double y2, int color);

/********update*******/
void update(t_data *data);
void render(t_data *data);

/*********data reader*********/
char	**readingdata(char *file);
int		countlines(char *file);
int		countwidth(char *file);


/*****rays casting******/
void castAllRays(t_data *data);
void exitfunc(void);


/******horiz and ver*****/
double	distancecalc(t_player first, t_vec sec);
double normalizeAngle(double angle);



/*********vert rays******/
// double vertical_rays(t_data *data, int ray);
t_vec vertical_rays(t_data *data, int ray);
t_vec horizontal_ray(t_data *data, int ray);
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
