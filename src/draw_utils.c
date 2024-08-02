#include "../include/fdf.h"

t_pixel	get_pixel(unsigned char *p_pixel)
{
	t_pixel	result;

	result.a = p_pixel;
	result.r = p_pixel + 1;
	result.g = p_pixel + 2;
	result.b = p_pixel + 3;
	return (result);
}

void draw_pixel(void *pixels, t_point point, int color)
{
	if (point.x < WIDTH && point.x > 0 && point.y < HEIGHT && point.y > 0)
	{
		int byte_per_pixel = 4;
		int column = (point.x * byte_per_pixel);
		int row = (point.y * byte_per_pixel * WIDTH);

		t_pixel pixel = get_pixel(pixels + row + column);
		*pixel.a =	(color >> 24)	& 0xFF;
		*pixel.r =	(color >> 16)	& 0xFF;
		*pixel.g =	(color >> 8)	& 0xFF;
		*pixel.b =	color		& 0xFF;
	}
}

void draw_line(void *pixels, t_point point0, t_point point1)
{
	int dx = abs(point1.x - point0.x);
	int sx = point0.x < point1.x ? 1 : -1;
	int dy = -abs(point1.y - point0.y);
	int sy = point0.y < point1.y ? 1 : -1;
	int error = dx + dy;
	
	while (1)
	{
		draw_pixel(pixels, point0, 0xFFFFFFFF); //TODO: implement plot
		if (point0.x == point1.x && point0.y == point1.y)
			break ;
		int e2 = 2 * error;
		if (e2 >= dy)
		{
			if (point0.x == point1.x) 
				break ;
			error = error + dy;
			point0.x = point0.x + sx;
		}
		if (e2 <= dx)
		{
			if (point0.y == point1.y)
				break ;
			error = error + dx;
			point0.y = point0.y + sy;
		}
	}
}

t_point	project_point(t_point point, float distance)
{
	t_point	result;
	float	z_projection;
	float	z;

	if (point.z == 0)
	{
		result.x = point.x + (WIDTH / 2);
		result.y = point.y + (HEIGHT / 2);
	}
	else
	{
		z_projection = distance / point.z;
		result.x = (int)(point.x * z_projection) + (WIDTH / 2);
		result.y = (int)(point.y * z_projection) + (HEIGHT / 2);
	}
	result.z = point.z;
	return (result);
}

void draw_map(t_map map, void *pixels)
{
	for (int i = 0; i < map.rows * map.cols; i++) {
		t_point point = map.points[i];
		//printf("X: %d, Y: %d, Z: %d\n", point.x, point.y, point.z);
		draw_pixel(pixels, point, 0xFFFFFFFF);
		//Draw line to the point at the right
		if (i % map.cols < (map.cols) - 1) {
			draw_line(pixels, point, map.points[i + 1]);
		}
		//Draw line to the point at the bottom
		if (i / map.cols < (map.rows) - 1) {
			draw_line(pixels, point, map.points[i + map.cols]);
		}
	}
}

t_point scale_point(double scale, t_point point)
{
	t_point result;

	result.x = point.x * scale;
	result.y = point.y * scale;
	result.z = point.z * scale;
	return (result);
}

t_point smooth_point(double smoothness, t_point point)
{
	t_point result;

	result.x = point.x;
	result.y = point.y;
	if (point.z > 0)
		result.z = point.z - 1/smoothness;
	else
		result.z = point.z + 1/smoothness;
	return (result);
}
