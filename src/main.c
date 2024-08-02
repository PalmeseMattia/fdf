#include "../include/fdf.h"

#define ESC 65307
#define ON_DESTROY 17

#define UP 65362
#define DOWN 65364
#define LEFT 65361
#define RIGHT 65363

#define W 119
#define S 115
#define PLUS 43
#define MINUS 45

int key_hook(int keycode, t_context *context)
{
	printf("Key pressed: %d\n", keycode);
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
	else if (keycode == W)
		context -> camera.distance += 50;
	else if (keycode == S) {
		if (context -> camera.distance > 0)
			context -> camera.distance -= 20;
	}
	else if (keycode == PLUS)
		context -> scale+=0.1;
	else if (keycode == MINUS)
	{
		if (context -> scale > 0)
			context -> scale-=0.1;
	}
	return 0;
}

int loop_hook(t_context *context)
{
	t_map map = context -> map;
	int map_size = map.rows * map.cols;
	static float rotation = 1.0;
	static t_point *points = NULL;
	
	t_point center = { .x = 0, .y = 0, .z = 0 };
	for (int i = 0; i < map_size; i++)
	{
		center.x += context->map.points[i].x;
		center.y += context->map.points[i].y;
		center.z += context->map.points[i].z;
	}
	center.x /= map_size;
	center.y /= map_size;
	center.z /= map_size;


	if (!points)
		points = malloc(map_size * sizeof(t_point));
	for (int i = 0; i < map_size; i++)
	{
		t_point p = context->map.points[i];
		
		// Translate to origin
		p.x -= center.x;
		p.y -= center.y;
		p.z -= center.z;
		
		//rotate point	
		//p = rotate_x(p, rotation);
		
		// Translate back
		p.x += center.x;
		p.y += center.y;
		p.z += center.z;

		// Add camera setoff
		p.x += context -> camera.x;
		p.y += context -> camera.y;
		p.z += context -> camera.z;
		
		p = scale_point(context -> scale, p);
		//p = smooth_point(context -> smoothness, p);
		points[i] = project_point(p, context -> camera.distance);
	}

	// Clear image
	for (int i = 0; i < (context->size_line * HEIGHT); i++)
	{
		*(char *)((context->pixels) + i) = 0x00;
	}

	draw_map((t_map){.points = points, .rows = map.rows, .cols = map.cols}, context -> pixels);
	mlx_put_image_to_window(context->mlx, context->win, context->image, 0, 0);
	rotation += 0.05;
	usleep(20000);
	return 0;
}

int destroy_hook(t_context *context)
{
	exit(EXIT_SUCCESS);
}

int main(int argc, char** argv)
{
	t_context	context;
	char		*filename;

	if (argc < 2)
	{
		printf("Please specify the map file.\nExample:\n$ ./fdf maps/42.fdf\n");
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

	// Parse the map
	context.map = (t_map){.points = NULL, .rows = 0, .cols = 0};
	get_map_size(filename, &context.map.rows, &context.map.cols);
	printf("ROWS: %d COLS: %d\n", context.map.rows, context.map.cols);
	context.map.points = (t_point *)malloc(sizeof(t_point) * (context.map.rows * context.map.cols));
	if (context.map.points == NULL) {
		perror("Failed to allocate map!");
		exit(EXIT_FAILURE);
	}
	parse_map(filename, &context);
	for(int i = 0; i < context.map.rows * context.map.cols; i++) {
		t_point p = context.map.points[i];
		printf("I: %d X: %d, Y: %d, Z: %d\n", i, p.x, p.y, p.z);
	}
	context.scale = 1.0;
	context.smoothness = 1.0;

	//free(context.map.points);
	draw_map(context.map, context.pixels);
	// Create camera
	context.camera = (t_camera){.x = 0, .y = 0, .z = 0, .distance = 20};

	mlx_put_image_to_window(context.mlx, context.win, context.image, 0, 0);
	// Add key hook
	mlx_key_hook(context.win, key_hook, &context);
	mlx_hook(context.win, ON_DESTROY, 0, destroy_hook, &context);
	mlx_loop_hook(context.mlx, loop_hook, &context);
	mlx_loop(context.mlx);
	return 0;
}

