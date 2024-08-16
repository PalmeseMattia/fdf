#include "../include/fdf.h"

#define ESC 65307
#define ON_DESTROY 17

#define UP 65362
#define DOWN 65364
#define LEFT 65361
#define RIGHT 65363

#define W 119
#define S 115
#define PLUS 236
#define MINUS 39
#define SCROLL_UP 4
#define SCROLL_DOWN 5
#define RIGHT_CLICK 1
#define LEFT_CLICK 3

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
	return 0;
}

int mouse_hook(int button, int x, int y, t_context *context)
{
	printf("Key pressed: %d at X: %d and Y: %d\n", button, x, y);
	if (button == SCROLL_UP)
		context -> scale += 1;
	else if (button == SCROLL_DOWN)
	{
		if (context -> scale > 0)
			context -> scale -= 1;
	}
	else if (button == LEFT_CLICK)
		context -> camera = (t_camera){.x = x, .y = y};
	return 0;
}

int loop_hook(t_context *context)
{
	t_map map = context -> map;
	int map_size = map.rows * map.cols;
	static float rotation = 1.0;
	static t_point *points = NULL;
	
	if (!points)
			points = malloc(map_size * sizeof(t_point));
	for (int i = 0; i < map_size; i++)
	{
		t_point p = context->map.points[i];
		// Scale
		p = scale_point(context -> scale, p);
		// Rotate
		p = rotate_x(p, rotation);
		p = rotate_y(p, rotation);
		p = rotate_z(p, rotation);
		// Add camera setoff
		p.x += context -> camera.x;
		p.y += context -> camera.y;
		points[i] = p;
	}
	// Clear image
	for (int i = 0; i < (context->size_line * HEIGHT); i++)
	{
		*(char *)((context->pixels) + i) = 0x00;
	}
	draw_map((t_map){.points = points, .rows = map.rows, .cols = map.cols}, context -> pixels);
	mlx_put_image_to_window(context->mlx, context->win, context->image, 0, 0);
	rotation += 0.05;
	usleep(40000);
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
	for(int i = 0; i < context.map.rows * context.map.cols; i++) {
		t_point p = context.map.points[i];
		//printf("I: %f X: %f, Y: %f, Z: %f\n", i, p.x, p.y, p.z);
	}
	context.scale = 10.0;
	context.smoothness = 1.0;

	//free(context.map.points);
	draw_map(context.map, context.pixels);
	// Create camera
	context.camera = (t_camera){.x = 0, .y = 0};

	mlx_put_image_to_window(context.mlx, context.win, context.image, 0, 0);
	// Add key hook
	mlx_key_hook(context.win, key_hook, &context);
	mlx_mouse_hook(context.win, mouse_hook, &context);
	mlx_hook(context.win, ON_DESTROY, 0, destroy_hook, &context);
	mlx_loop_hook(context.mlx, loop_hook, &context);
	mlx_loop(context.mlx);
	return 0;
}

