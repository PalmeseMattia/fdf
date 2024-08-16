/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <dpalmese@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:35:37 by dpalmese          #+#    #+#             */
/*   Updated: 2024/08/16 11:35:55 by dpalmese         ###   ########.fr       */
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
