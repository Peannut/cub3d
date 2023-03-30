/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:59:54 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/30 16:19:27 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <math.h>
# include <mlx.h>
# include <stdbool.h>

# define BLOCK 32
# define PI 3.1415926535
# define FOV_ANGEL 60
# define WALL_STRIP_WIDTH 30
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define MINIMAP_SCALE 0.2
// fov angel in radiant btw :)
typedef struct s_ray
{
	double	ray_angle;
	double	x;
	double	y;
	double	distance;
	bool	hit_vertical;
	bool	hit_horizontal;
	int		ray_facing_down;
	int		ray_facing_up;
	int		ray_facing_left;
	int		ray_facing_right;
	int		hitx;
	int		hity;
	int		wallheight;
}	t_ray;

typedef struct s_texture
{
	char	*info;
	char	*path;
	void	*img;
	int		width;
	int		height;
}	t_texture;
typedef struct s_player
{
	double	x;
	double	y;
	double	rotation_angle;
	int		sidewaysdirection;
	int		turndirection;
	int		walkdirection;
	double	movespeed;
	double	rotationspeed;
	double	dx;
	double	dy;
	char	spawn;
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
}	t_info;

typedef struct data {
	void		*mlx;
	void		*mlx_win;
	void		*frame;
	void		*text;
	int			height;
	int			width;
	int			raysnumba;
	double		fov;
	int			color;
	t_ray		rays[WIN_WIDTH];
	t_info		*info;
	t_player	player;
	t_texture	img;
}	t_data;

typedef struct s_img {
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;
typedef struct s_color
{
	char	*tmp;
	char	**arr;
	char	**hold2;
	int		*rgb;
	int		i;
}	t_color;
typedef struct s_vec
{
	int	x;
	int	y;
}	t_vec;
typedef struct s_minimap{
	int	width;
	int	height;
	int	centerx;
	int	centery;
	int	radius;
	int	startx;
	int	starty;
	int	endx;
	int	endy;
}	t_minimap;

int			count_lines(char **map);
int			get_longest_line(char **map);
void		print_map(char **map);
void		init_the_map(char *map_name);
void		ft_error(char *msg);
int			exitfunc(t_data *data);

/************drawing*******/
void		my_pixel_put(void *img, int x, int y, int color);
char		**allocate_map(char **map, int i);
void		draw_map(t_data *data);
void		draw_grid(t_data *data);
void		draw_player(t_data *data, int flag);
void		draw_line2(void *img, t_vec *var1, t_vec *var2, int color);

/********update*******/
void		update(t_data *data);
void		render(t_data *data);

/*********data reader*********/
t_info		*ft_parse(char **av, t_data *data);
int			countlines(char *file);
int			countwidth(char *file);

/*****rays casting******/
void		cast_all_rays(t_data *data);

/******horiz and ver*****/
double		distancecalc(t_player first, t_vec sec);
double		normalize_angle(double angle);

/*********vert rays******/
// double vertical_rays(t_data *data, int ray);
t_vec		vertical_rays(t_data *data, int ray);
t_vec		horizontal_ray(t_data *data, int ray);
void		hitsave(t_data *data, bool val1, bool val2, int ray);
void		findverticalsteps(t_data *data, t_vec *intercept, int ray);
void		draw_ceiling_and_floor(t_data *data);
void		render_ceiling(t_data *data, int x, int wallheight);
void		render_floor(t_data *data, int x, int wallheight);
/*************mouse***********/

int			mouse_event(int x, int y, void *data);
int			mlx_mouse_hide(void);
int			mlx_mouse_move(void *win_ptr, int x, int y);

/************PARSING*********/

void		ft_error(char *msg);
int			ft_scan_map(char **map, t_info *info);
void		check_extension(char **map_file);
char		*read_file(char **av, t_info *info);
t_info		*ft_parse(char **av, t_data *data);
int			ft_extract_data(t_tools *tl, t_info *info, char **map, int i);
void		valid_player(char **map, t_data *data);
void		check_map_components(char **map);
int			is_valid_component(char ch, t_data *data, int i, int j);

int			valid_rgb_help(char *s);
void		rgb_handling(int rgb);
int			*valid_rgb(t_color *color);
int			*ft_check_colors(char *map);

void		north(char *map, t_info *info);
void		south(char *map, t_info *info);
void		east(char *map, t_info *info);
void		west(char *map, t_info *info);
void		ft_floor(char *map, t_info *info);
void		ft_ceilling(char *map, t_info *info);

void		check_lines(char **map, int l_nbr, t_tools el);
int			check_path(char *path);
void		check_previous(int now, char *previous, char *next);
int			check_extrm(char **map, int i, int j);
void		check_directions(char **map);

void		ft_free(char **s);
void		free_map(char **map, int num_lines);

void		initialize(t_info *info);
t_tools		initialize_tools(void);
int			scan_line(char *map);
int			is_spaces(char *line);
int			skip_whitespace(char *s);
char		*end_spaces(char *s);

/****casting_rays_utils*/
double		normalize_angle(double angle);
void		find_ray_face(t_data *data, int ray);
double		distancecalc(t_player valone, t_vec valtwo);
int			get_color_from_texture(t_data *data, int y, int ray,
				int wallheight);
void		*get_texture(char *file, t_data *data);
void		projection(t_data *data);
/*****utils*/
int			thebiggestlen(t_data *data);
size_t		ptrline(char **str);
void		init_rotationangel(t_data *data);
int			key_press(int keycode, void *param);
int			key_release(int keycode, void *param);

/***********minimap************/
void		calculate_visible_map(t_data *data, t_minimap *minimap);
void		draw_minimap_circle(t_data *data, t_minimap *minimap);
int			get_map_color(char c);
t_minimap	init_minimap(void);
#endif