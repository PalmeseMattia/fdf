/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <dpalmese@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:32:30 by dpalmese          #+#    #+#             */
/*   Updated: 2024/08/15 14:33:52 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_point	rotate_x(t_point point, float angle)
{
	t_point	result;

	result.x = point.x;
	result.y = (int)((point.y * cos(angle)) - (point.z * sin(angle)));
	result.z = (int)((point.y * sin(angle)) + (point.z * cos(angle)));
	return (result);
}

t_point	rotate_y(t_point point, float angle)
{
	t_point	result;

	result.x = (int)((point.x * cos(angle)) + (point.z * sin(angle)));
	result.y = point.y;
	result.z = (int)(-(point.x * sin(angle)) + (point.z * cos(angle)));
	return (result);
}

t_point	rotate_z(t_point point, float angle)
{
	t_point	result;

	result.x = (int)((point.x * cos(angle)) - (point.y * sin(angle)));
	result.y = (int)((point.x * sin(angle)) + (point.y * cos(angle)));
	result.z = point.z;
	return (result);
}
