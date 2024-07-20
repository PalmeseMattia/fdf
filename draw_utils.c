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

void draw_pixel(t_context context, t_point point, int color)
{
	if (point.x < WIDTH && point.x > 0 && point.y < HEIGHT && point.y > 0)
	{
		int byte_per_pixel = 4;
		int column = (point.x * byte_per_pixel);
		int row = (point.y * context.size_line);

		t_pixel pixel = get_pixel(context.pixels + row + column);
		*pixel.a =	(color >> 24)	& 0xFF;
		*pixel.r =	(color >> 16)	& 0xFF;
		*pixel.g =	(color >> 8)	& 0xFF;
		*pixel.b =	color		& 0xFF;
	}
}

void draw_line(t_context context, t_point point0, t_point point1)
{
	int dx = abs(point1.x - point0.x);
	int sx = point0.x < point1.x ? 1 : -1;
	int dy = -abs(point1.y - point0.y);
	int sy = point0.y < point1.y ? 1 : -1;
	int error = dx + dy;
	
	while (1)
	{
		draw_pixel(context, point0, 0xFFFFFFFF); //TODO: implement plot
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

void draw_map(t_context context)
{
	t_map map = context.map;
	for (int i = 0; i < map.rows * map.cols; i++) {
		t_point point = map.points[i];
		printf("X: %d, Y: %d, Z: %d\n", point.x, point.y, point.z);
		draw_pixel(context, point, 0xFFFFFFFF);
		//Draw line to the point at the right
		if (i % map.cols < (map.cols) - 1) {
			draw_line(context, point, map.points[i + 1]);
		}
		//Draw line to the point at the bottom
		if (i / map.rows < (map.rows) - 1) {
			draw_line(context, point, map.points[i + map.cols]);
		}
	}


}
