#ifndef FDF_H
# define FDF_H

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 1920
#define HEIGHT 1080

typedef struct s_pixel
{
	unsigned char	*r;
	unsigned char	*g;
	unsigned char	*b;
	unsigned char	*a;
}	t_pixel;

typedef struct s_point
{
	int x;
	int y;
	int z;
}	t_point;

typedef struct s_map
{
	t_point	*points;
	int	rows;
	int	cols;
}	t_map;

typedef struct s_context
{
	void	*mlx;
	void	*win;
	void	*image;
	void	*pixels;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	t_map	map;
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
void 	draw_pixel(t_context context, t_point point, int color);
void 	draw_line(t_context context, t_point point0, t_point point1);
void 	draw_map(t_context context);

#endif
