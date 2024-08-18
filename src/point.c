/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <dpalmese@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:35:37 by dpalmese          #+#    #+#             */
/*   Updated: 2024/08/18 02:10:34 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_point	new_point(double x, double y, double z, double color)
{
	t_point	result;

	result.x = x;
	result.y = y;
	result.z = z;
	result.color = color;
	return (result);
}

t_point	scale_point(double scale, t_point point)
{
	t_point	result;

	result.x = point.x * scale;
	result.y = point.y * scale;
	result.z = point.z * scale;
	return (result);
}

t_point	rotate_point(t_rotations rotations, t_point point)
{
	t_point	result;

	result = rotate_x(point, rotations.x);
	result = rotate_y(result, rotations.y);
	result = rotate_z(result, rotations.z);
	return (result);
}
