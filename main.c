#include "fdf.h"

#define HEIGHT 1080
#define WIDTH 1920
#define ESC 65307
#define ON_DESTROY 17


int	key_hook(int keycode, t_context *context)
{
	printf("Key pressed: %d\n", keycode);
	if (keycode == ESC) 
	{
		mlx_destroy_window(context -> mlx, context -> win);
		exit(EXIT_SUCCESS);
	}
	return 0;
}

int	loop_hook(t_context *context)
{
	return 0;
}

int destroy_hook(t_context *context)
{
	exit(EXIT_SUCCESS);
}

int main()
{
	t_context context;
	int m[16] = {	1,1,1,1,
			1,2,2,1,
			1,2,2,1,
			1,1,1,1};
	int map_size = 16;
	int map_rows = 4;
	int map_cols = 4;
	int color = 0xFFFFFFFF;

	context.mlx = mlx_init();
	if (!context.mlx) {
		perror("MLX Error encountered while opening a connection!");
		exit(EXIT_FAILURE);
	}
	
	//WINDOW CREATION
	context.win = mlx_new_window(context.mlx, WIDTH, HEIGHT, "FDF");

	//IMAGE CREATION
	context.image = mlx_new_image(context.mlx, WIDTH, HEIGHT);
	context.pixels = mlx_get_data_addr(context.image, &context.bits_per_pixel, &context.size_line, &context.endian);
	
	//CREATE A SAMPLE MAP
	t_point *points = (t_point *)malloc(16 * sizeof(t_point));
	for(int i = 0; i < 16; i++) {
		points[i] = (t_point){((i % map_cols) + 10) *40, (((i / map_rows) + 10) *40), m[i]}; //TODO: remove hardcoded scale factors
	}
	t_map map = {.points = points, .rows = 4, .cols = 4};
	context.map = map;

	//ITERATE MAP AND DRAW POINTS
	draw_map(context);

	//DRAW IMAGE
	mlx_put_image_to_window(context.mlx, context.win, context.image, 0, 0);
	
	//ADD KEY HOOK
	mlx_key_hook(context.win, key_hook, &context);
	mlx_hook(context.win, ON_DESTROY, 0, destroy_hook, &context);
	mlx_loop_hook(context.mlx, loop_hook, &context);
	mlx_loop(context.mlx);
	return (0);
}


