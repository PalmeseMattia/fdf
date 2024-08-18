/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <dpalmese@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:53:25 by dpalmese          #+#    #+#             */
/*   Updated: 2024/08/18 02:18:50 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fdf.h"

void	set_hooks(t_context *context)
{
	mlx_key_hook(context->win, key_hook, context);
	mlx_mouse_hook(context->win, mouse_hook, context);
	mlx_hook(context->win, ON_DESTROY, 0, destroy_hook, context);
	mlx_loop_hook(context->mlx, loop_hook, context);
	mlx_hook(context->win, 2, 1, key_press, context);
}

int	main(int argc, char **argv)
{
	t_context	context;
	char		*filename;

	if (argc < 2)
	{
		ft_printf("Please specify a map file.\n");
		exit(EXIT_FAILURE);
	}
	filename = argv[1];
	context.mlx = mlx_init();
	if (!context.mlx)
	{
		perror("MLX Error encountered while opening a connection!");
		exit(EXIT_FAILURE);
	}
	context.win = mlx_new_window(context.mlx, WIDTH, HEIGHT, "FDF");
	context.image = mlx_new_image(context.mlx, WIDTH, HEIGHT);
	context.pixels = mlx_get_data_addr(context.image, &context.bits_per_pixel, &context.size_line, &context.endian);
	context.map = (t_map){.points = NULL, .rows = 0, .cols = 0};
	// TODO: check file exists
	int fd = open(filename, O_RDONLY);
	get_map_size(fd, &context.map.rows, &context.map.cols);
	close(fd);
	fd = open(filename, O_RDONLY);
	context.map.points = (t_point *)malloc(sizeof(t_point) * (context.map.rows * context.map.cols));
	if (context.map.points == NULL)
	{
		perror("Failed to allocate map!");
		exit(EXIT_FAILURE);
	}
	// Parse the map
	parse_map(fd, &context.map);
	
	context.scale = 10.0;
	context.spinning = 0;
	draw_map(context.map, context.pixels);
	context.camera = (t_camera){.x = WIDTH/2, .y = HEIGHT/2};
	mlx_put_image_to_window(context.mlx, context.win, context.image, 0, 0);
	// Add key hook
	set_hooks(&context);
	mlx_loop(context.mlx);
	return (0);
}
