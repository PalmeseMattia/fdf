/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <dpalmese@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:06:03 by dpalmese          #+#    #+#             */
/*   Updated: 2024/08/17 22:04:52 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	key_hook(int keycode, t_context *context)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(context->mlx, context->win);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == UP)
		context -> camera.y -= 40;
	else if (keycode == DOWN)
		context -> camera.y += 40;
	else if (keycode == LEFT)
		context -> camera.x -= 40;
	else if (keycode == RIGHT)
		context -> camera.x += 40;
	return (0);
}

int	mouse_hook(int button, int x, int y, t_context *context)
{
	if (button == SCROLL_UP)
		context -> scale += 0.5;
	else if (button == SCROLL_DOWN)
	{
		if (context -> scale > 0)
			context -> scale -= 0.5;
	}
	else if (button == LEFT_CLICK)
		context -> camera = (t_camera){.x = x, .y = y};
	return (0);
}

int	loop_hook(t_context *context)
{
	static t_point	*points = NULL;
	t_map			map;
	t_point			p;
	int				i;

	i = 0;
	map = context -> map;
	if (!points)
		points = malloc(map.rows * map.cols * sizeof(t_point));
	while (i < map.rows * map.cols)
	{
		p = context->map.points[i];
		p = scale_point(context -> scale, p);
		p = rotate_x(p, context -> rotations.x);
		p = rotate_y(p, context -> rotations.y);
		p = rotate_z(p, context -> rotations.z);
		p.x += context -> camera.x;
		p.y += context -> camera.y;
		points[i++] = p;
	}
	map.points = points;
	clean_map(context, map);
	draw_map(map, context -> pixels);
	mlx_put_image_to_window(context->mlx, context->win, context->image, 0, 0);
	return (0);
}

int	destroy_hook(t_context *context)
{
	mlx_destroy_window(context->mlx, context->win);
	exit (EXIT_SUCCESS);
}
