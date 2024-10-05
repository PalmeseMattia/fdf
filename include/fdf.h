/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <dpalmese@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 08:04:43 by dpalmese          #+#    #+#             */
/*   Updated: 2024/10/05 08:08:12 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FDF_H
# define FDF_H

# include "../mlx_linux/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "../libs/libft/libft.h"

# define WIDTH 1920
# define HEIGHT 1080
// Close events
# define ESC 65307
# define ON_DESTROY 17
// Arrows
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
// Keystrokes
# define W 119
# define S 115
# define A 97
# define D 100
# define Q 113
# define E 101
# define PLUS 236
# define MINUS 39
# define SPACE 32
// Mouse
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define RIGHT_CLICK 1
# define LEFT_CLICK 3

typedef struct s_rotations
{
	double	x;
	double	y;
	double	z;
}	t_rotations;

typedef struct s_camera
{
	float	x;
	float	y;
}	t_camera;

typedef struct s_pixel
{
	unsigned char	*r;
	unsigned char	*g;
	unsigned char	*b;
	unsigned char	*a;
}	t_pixel;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	double	color;
}	t_point;

typedef struct s_map
{
	t_point	*points;
	int		rows;
	int		cols;
}	t_map;

typedef struct s_context
{
	void		*mlx;
	void		*win;
	void		*image;
	void		*pixels;
	t_rotations	rotations;
	t_map		map;
	t_camera	camera;
	double		scale;
	int			bpp;
	int			size_line;
	int			endian;
	int			spinning;
}	t_context;

typedef struct s_image
{
	void	*image;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*pixels;
}	t_image;

t_pixel	get_pixel(unsigned char *p_pixel);
void	draw_pixel(void *pixels, t_point point, int color);
void	draw_line(void *pixels, t_point point0, t_point point1);
void	draw_map(t_map map, void *pixels);
t_point	project_point(t_point point, float fov);
t_point	rotate_x(t_point point, float angle);
t_point	rotate_y(t_point point, float angle);
t_point	rotate_z(t_point point, float angle);
void	parse_map(int fd, t_map *m);
void	get_map_size(int fd, int *rows, int*cols);
t_point	scale_point(double scale, t_point point);
t_point	smooth_point(double smoothness, t_point point);
int		mouse_hook(int button, int x, int y, t_context *context);
t_point	new_point(double x, double y, double z, double color);
// Hooks
int		key_hook(int keycode, t_context *context);
int		mouse_hook(int button, int x, int y, t_context *context);
int		loop_hook(t_context *context);
int		destroy_hook(t_context *context);
void	clean_map(t_context *context, t_map map);
int		key_press(int keycode, t_context *context);
t_point	rotate_point(t_rotations rotations, t_point point);
void	spin(t_context *context, double angle);

#endif
