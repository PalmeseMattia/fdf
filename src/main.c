/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <dpalmese@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:53:25 by dpalmese          #+#    #+#             */
/*   Updated: 2024/10/05 08:24:54 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fdf.h"
#define MLXD mlx_get_data_addr 

void	set_hooks(t_context *context)
{
	mlx_key_hook(context->win, key_hook, context);
	mlx_mouse_hook(context->win, mouse_hook, context);
	mlx_hook(context->win, ON_DESTROY, 0, destroy_hook, context);
	mlx_loop_hook(context->mlx, loop_hook, context);
	mlx_hook(context->win, 2, 1, key_press, context);
}

void	initialize_context(t_context *c)
{
	c -> mlx = mlx_init();
	if (!c -> mlx)
	{
		perror("MLX Error encountered while opening a connection!");
		exit(EXIT_FAILURE);
	}
	c -> win = mlx_new_window(c -> mlx, WIDTH, HEIGHT, "FDF");
	c -> image = mlx_new_image(c -> mlx, WIDTH, HEIGHT);
	c -> pixels = MLXD(c -> image, &c -> bpp, &c -> size_line, &c -> endian);
	c -> map = (t_map){.points = NULL, .rows = 0, .cols = 0};
	c -> camera = (t_camera){.x = WIDTH / 2, .y = HEIGHT / 2};
	c -> scale = 10.0;
	c -> spinning = 0;
}

void	read_map(char *filename, t_context *c)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Please specify a valid map file!\n");
		exit(EXIT_FAILURE);
	}
	get_map_size(fd, &c -> map.rows, &c -> map.cols);
	close(fd);
	fd = open(filename, O_RDONLY);
	c -> map.points = malloc(sizeof(t_point) * (c -> map.rows * c -> map.cols));
	if (c -> map.points == NULL)
	{
		perror("Failed to allocate map!");
		exit(EXIT_FAILURE);
	}
	parse_map(fd, &c -> map);
}

int	main(int argc, char **argv)
{
	char		*filename;
	t_context	c;

	if (argc < 2)
	{
		ft_printf("Please specify a map file.\n");
		exit(EXIT_FAILURE);
	}
	filename = argv[1];
	initialize_context(&c);
	read_map(filename, &c);
	draw_map(c.map, c.pixels);
	mlx_put_image_to_window(c.mlx, c.win, c.image, 0, 0);
	set_hooks(&c);
	mlx_loop(c.mlx);
	return (0);
}
