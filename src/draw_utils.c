/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <dpalmese@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:07:10 by dpalmese          #+#    #+#             */
/*   Updated: 2024/08/16 11:57:57 by dpalmese         ###   ########.fr       */
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
	int		byte_per_pixel;
	int		column;
	int		row;
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
	if (point0.x < point1.x)
		sx = 1;
   	else
		sx = -1;
	dy = -abs(point1.y - point0.y);
	if(point0.y < point1.y) 
		sy = 1;
	else
		sy = -1;
	error = dx + dy;
	while (1)
	{
		draw_pixel(pixels, point0, 0xFFFF00FF);
		if (point0.x == point1.x && point0.y == point1.y)
			break ;
		if (2 * error >= dy)
		{
			if (point0.x == point1.x)
				break ;
			error = error + dy;
			point0.x = point0.x + sx;
		}
		if (2 * error <= dx)
		{
			if (point0.y == point1.y)
				break ;
			error = error + dx;
			point0.y = point0.y + sy;
		}
	}
}

void	draw_map(t_map map, void *pixels)
{
	int		i;
	t_point	point;

	i = 0;
	while (i < map.rows * map.cols)
	{
		point = map.points[i];
		draw_pixel(pixels, point, 0xFFFFFFFF);
		if (i % map.cols < (map.cols) - 1)
			draw_line(pixels, point, map.points[i + 1]);
		if (i / map.cols < (map.rows) - 1)
			draw_line(pixels, point, map.points[i + map.cols]);
		i++;
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
