/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <dpalmese@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:48:57 by dpalmese          #+#    #+#             */
/*   Updated: 2024/08/16 16:15:09 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	set_sx_sy(t_point p0, t_point p1, int *sx, int *sy)
{
	if (p0.x < p1.x)
		*sx = 1;
	else
		*sx = -1;
	if (p0.y < p1.y)
		*sy = 1;
	else
		*sy = -1;
}

void	set_dx_dy(t_point p0, t_point p1, int *dx, int *dy)
{
	*dx = abs(p1.x - p0.x);
	*dy = -abs(p1.y - p0.y);
}

void	update_x(int *error, t_point *point, int dy, int sx)
{
	*error += dy;
	point -> x += sx;
}

void	update_y(int *error, t_point *point, int dx, int sy)
{
	*error += dx;
	point -> y += sy;
}

void	draw_line(void *pixels, t_point point0, t_point point1)
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	error;

	set_sx_sy(point0, point1, &sx, &sy);
	set_dx_dy(point0, point1, &dx, &dy);
	error = dx + dy;
	while (1)
	{
		draw_pixel(pixels, point0, 0xFFFFFFFF);
		if (2 * error >= dy)
		{
			if (point0.x == point1.x)
				break ;
			update_x(&error, &point0, dy, sx);
		}
		if (2 * error <= dx)
		{
			if (point0.y == point1.y)
				break ;
			update_y(&error, &point0, dx, sy);
		}
	}
}
