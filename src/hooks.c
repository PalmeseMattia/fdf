/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <dpalmese@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:06:03 by dpalmese          #+#    #+#             */
/*   Updated: 2024/08/17 18:14:20 by dpalmese         ###   ########.fr       */
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
	t_map			map;
	t_point			p;
	static float	rotation = 1.0;
	static t_point	*points = NULL;
	int				i;

	i = 0;
	map = context -> map;
	if (!points)
		points = malloc(map.rows * map.cols * sizeof(t_point));
	while (i < map.rows * map.cols)
	{
		p = context->map.points[i];
		p = scale_point(context -> scale, p);	// Scale
		p = rotate_x(p, rotation);				// Rotate
		p = rotate_y(p, rotation);
		p = rotate_z(p, rotation);
		p.x += context -> camera.x;				//Traslate
		p.y += context -> camera.y;
		points[i++] = p;
	}
	for (int i = 0; i < (context->size_line * HEIGHT); i++)
	{
		*(char *)((context->pixels) + i) = 0x00;
	}
	draw_map((t_map){.points = points, .rows = map.rows, .cols = map.cols}, context -> pixels);
	mlx_put_image_to_window(context->mlx, context->win, context->image, 0, 0);
	rotation += 0.05;
	usleep(20000);
	return (0);
}

int	destroy_hook(t_context *context)
{
	mlx_destroy_window(context->mlx, context->win);
	exit (EXIT_SUCCESS);
}
