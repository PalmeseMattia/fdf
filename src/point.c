/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <dpalmese@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:35:37 by dpalmese          #+#    #+#             */
/*   Updated: 2024/08/16 14:23:13 by dpalmese         ###   ########.fr       */
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
