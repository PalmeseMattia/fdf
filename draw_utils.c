#include "fdf.h"

t_pixel	get_pixel(unsigned char *p_pixel)
{
	t_pixel	result;

	result.a = p_pixel;
	result.r = p_pixel + 1;
	result.g = p_pixel + 2;
	result.b = p_pixel + 3;
	return (result);
}


