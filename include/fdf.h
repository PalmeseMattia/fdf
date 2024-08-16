#ifndef FDF_H
# define FDF_H

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include "../libs/libft/libft.h"

#define WIDTH 1920
#define HEIGHT 1080

typedef struct s_camera
{
	float x;
	float y;
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
	double x;
	double y;
	double z;
	double color;
}	t_point;

typedef struct s_map
{
	t_point	*points;
	int	rows;
	int	cols;
}	t_map;

typedef struct s_context
{
	void		*mlx;
	void		*win;
	void		*image;
	void		*pixels;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	t_map		map;
	t_camera	camera;
	double		scale;
	double		smoothness;
}	t_context;

typedef struct s_image
{
	void	*image;
	int	bits_per_pixel;
	int	size_line;
	int	endian;
	char	*pixels;
}	t_image;

t_pixel	get_pixel(unsigned char *p_pixel);
void draw_pixel(void *pixels, t_point point, int color);
void 	draw_line(void *pixels, t_point point0, t_point point1);
void 	draw_map(t_map map, void *pixels);
t_point	project_point(t_point point, float fov);
t_point rotate_x(t_point point, float angle);
t_point rotate_y(t_point point, float angle);
t_point rotate_z(t_point point, float angle);
void	parse_map(int fd, t_map *m);
void get_map_size(int fd, int *rows, int*cols);
t_point scale_point(double scale, t_point point);
t_point smooth_point(double smoothness, t_point point);
int mouse_hook(int button, int x, int y, t_context *context);
t_point	new_point(double x, double y, double z, double color);

#endif
