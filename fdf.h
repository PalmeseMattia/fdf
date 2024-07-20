#ifndef FDF_H
# define FDF_H

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_pixel
{
	unsigned char	*r;
	unsigned char	*g;
	unsigned char	*b;
	unsigned char	*a;
}	t_pixel;

t_pixel	get_pixel(unsigned char *p_pixel);

#endif
