/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <dpalmese@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:07:10 by dpalmese          #+#    #+#             */
/*   Updated: 2024/08/15 15:14:46 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	draw_pixel(void *pixels, t_point point, int color)
{
	int	byte_per_pixel;
	int	column;
	int	row;
	t_pixel	pixel;

	if (point.x < WIDTH && point.x > 0 && point.y < HEIGHT && point.y > 0)
	{
		byte_per_pixel = 4;
		column = ((int)point.x * byte_per_pixel);
		row = ((int)point.y * byte_per_pixel * WIDTH);
		pixel = get_pixel(pixels + row + column);
		*pixel.a = (color >> 24) & 0xFF;
		*pixel.r = (color >> 16) & 0xFF;
		*pixel.g = (color >> 8) & 0xFF;
		*pixel.b = color & 0xFF;
	}
}

void	draw_line(void *pixels, t_point point0, t_point point1)
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	error;

	dx = abs(point1.x - point0.x);
	sx = point0.x < point1.x ? 1 : -1;
	dy = -abs(point1.y - point0.y);
	sy = point0.y < point1.y ? 1 : -1;
	error = dx + dy;
	while (1)
	{
		draw_pixel(pixels, point0, 0xFFFF00FF);
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

t_point	scale_point(double scale, t_point point)
{
	t_point	result;
	
	result.x = point.x * scale;
	result.y = point.y * scale;
	result.z = point.z * scale;
	return (result);
}
