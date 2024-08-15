#include "../include/fdf.h"

t_point	new_point(double x, double y, double z, double color)
{
	t_point result;

	result.x = x;
	result.y = y;
	result.z = z;
	result.color = color;
	return (result);
}
