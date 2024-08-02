#include "../include/fdf.h"

#define ESC 65307
#define ON_DESTROY 17

#define UP 65362
#define DOWN 65364
#define LEFT 65361
#define RIGHT 65363

#define W 119
#define S 115

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
	return 0;
}

int loop_hook(t_context *context)
{
	static float rotation = 1.0;
	// Calculate the center of the cube
	t_point center = { .x = 0, .y = 0, .z = 0 };
	for (int i = 0; i < 8; i++)
	{
		center.x += context->map.points[i].x;
		center.y += context->map.points[i].y;
		center.z += context->map.points[i].z;
	}
	center.x /= 8;
	center.y /= 8;
	center.z /= 8;

	// Clear image
	for (int i = 0; i < (context->size_line * HEIGHT); i++)
	{
		*(char *)((context->pixels) + i) = 0x00;
	}

	// Rotate points
	t_point points[8];
	for (int i = 0; i < 8; i++)
	{
		t_point p = context->map.points[i];

		// Translate to origin
		p.x -= center.x;
		p.y -= center.y;
		p.z -= center.z;

		// Apply rotations
		p = rotate_x(p, rotation);
		p = rotate_y(p, rotation);
		p = rotate_z(p, rotation);

		// Translate back
		p.x += center.x;
		p.y += center.y;
		p.z += center.z;

		// Add camera setoff
		p.x += context -> camera.x;
		p.y += context -> camera.y;
		p.z += context -> camera.z;
		
		points[i] = project_point(p, context -> camera.distance);

		//printf("I: %d X: %d Y: %d Z: %d\n", i, points[i].x, points[i].y, points[i].z);
	}

	// Draw cube edges
	draw_line(*context, points[0], points[1]);
	draw_line(*context, points[0], points[2]);
	draw_line(*context, points[0], points[4]);
	draw_line(*context, points[2], points[3]);
	draw_line(*context, points[2], points[6]);
	draw_line(*context, points[1], points[3]);
	draw_line(*context, points[1], points[5]);
	draw_line(*context, points[4], points[5]);
	draw_line(*context, points[4], points[6]);
	draw_line(*context, points[6], points[7]);
	draw_line(*context, points[5], points[7]);
	draw_line(*context, points[3], points[7]);

	mlx_put_image_to_window(context->mlx, context->win, context->image, 0, 0);
	rotation += 0.05;
	usleep(20000);
	return 0;
}

int destroy_hook(t_context *context)
{
	exit(EXIT_SUCCESS);
}

int main()
{
	t_context context;

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

	// Create a sample map
	t_point *points = (t_point *)malloc(8 * sizeof(t_point));
	points[0] = (t_point){.x = 100, .y = 100, .z = 100};
	points[1] = (t_point){.x = 200, .y = 100, .z = 100};
	points[2] = (t_point){.x = 100, .y = 100, .z = 200};
	points[3] = (t_point){.x = 200, .y = 100, .z = 200};
	points[4] = (t_point){.x = 100, .y = 200, .z = 100};
	points[5] = (t_point){.x = 200, .y = 200, .z = 100};
	points[6] = (t_point){.x = 100, .y = 200, .z = 200};
	points[7] = (t_point){.x = 200, .y = 200, .z = 200};

	context.map = (t_map){.points = points, .rows = 0, .cols = 0};
	context.camera = (t_camera){0, 0, 0, 200};

	// Add key hook
	mlx_key_hook(context.win, key_hook, &context);
	mlx_hook(context.win, ON_DESTROY, 0, destroy_hook, &context);
	mlx_loop_hook(context.mlx, loop_hook, &context);
	mlx_loop(context.mlx);
	return 0;
}

