/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <dpalmese@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:53:25 by dpalmese          #+#    #+#             */
/*   Updated: 2024/08/17 18:13:58 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	main(int argc, char** argv)
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
	// Window creation
	context.win = mlx_new_window(context.mlx, WIDTH, HEIGHT, "FDF");
	// Image creation
	context.image = mlx_new_image(context.mlx, WIDTH, HEIGHT);
	context.pixels = mlx_get_data_addr(context.image, &context.bits_per_pixel, &context.size_line, &context.endian);
	// Get map size
	context.map = (t_map){.points = NULL, .rows = 0, .cols = 0};
	// TODO: check file exists
	int fd = open(filename, O_RDONLY);
	get_map_size(fd, &context.map.rows, &context.map.cols);
	close(fd);
	fd = open(filename, O_RDONLY);
	// Alloc points
	context.map.points = (t_point *)malloc(sizeof(t_point) * (context.map.rows * context.map.cols));
	if (context.map.points == NULL) {
		perror("Failed to allocate map!");
		exit(EXIT_FAILURE);
	}
	// Parse the map
	printf("Parsing the map\n");
	parse_map(fd, &context.map);
	
	context.scale = 10.0;
	//free(context.map.points);
	draw_map(context.map, context.pixels);
	// Create camera
	context.camera = (t_camera){.x = WIDTH/2, .y = HEIGHT/2};

	mlx_put_image_to_window(context.mlx, context.win, context.image, 0, 0);
	// Add key hook
	mlx_key_hook(context.win, key_hook, &context);
	mlx_mouse_hook(context.win, mouse_hook, &context);
	mlx_hook(context.win, ON_DESTROY, 0, destroy_hook, &context);
	mlx_loop_hook(context.mlx, loop_hook, &context);
	mlx_loop(context.mlx);
	return 0;
}
