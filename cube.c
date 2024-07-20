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

t_point rotate_x(t_point point, float angle)
{
	t_point result;

	result.x = point.x;
	result.y = (int)((point.y * cos(angle)) - (point.z * sin(angle)));
	result.z = (int)((point.y * sin(angle)) + (point.z * cos(angle)));
	return result;
}

t_point rotate_y(t_point point, float angle)
{
	t_point result;

	result.x = ((point.x * cos(angle)) + (point.z * sin(angle)));
	result.y = point.y;
	result.z = (-(point.x * sin(angle)) + (point.z * cos(angle)));
	return result;
}

t_point rotate_z(t_point point, float angle)
{
	t_point result;

	result.x = ((point.x * cos(angle)) - (point.y * sin(angle)));
	result.y = ((point.x * sin(angle)) + (point.y * cos(angle)));
	result.z = point.z;
	return result;
}

int	loop_hook(t_context *context)
{
	static float rotation = 1.0;
	//t_point *points = context -> map.points;

	//CLEAR IMAGE

	t_point points[8];

	for(int i = 0; i < (context -> size_line * HEIGHT); i++) {
		*(char *)((context -> pixels) + i) = 0x00;
	}

	for(int i = 0; i < 8; i++) {
		points[i] = rotate_x(context -> map.points[i], rotation);
		points[i] = rotate_y(points[i], rotation);
		points[i] = rotate_z(points[i], rotation);
		points[i] = project_point((points[i]), 1000.0);
		printf("I: %d X: %d Y: %d Z: %d\n", i, points[i].x, points[i].y, points[i].z);
	}
	//TOP LEFT TO RIGHT
	draw_line(*context, points[0], points[1]);
	//TOP LEFT TO BEHIND
	draw_line(*context, points[0], points[2]);
	//TOP LEFT TO BOTTOM
	draw_line(*context, points[0], points[4]);
	//BACK LEFT TO RIGHT
	draw_line(*context, points[2], points[3]);
	//BACK LEFT TO BOTTOM
	draw_line(*context, points[2], points[6]);
	//TOP RIGHT TO BEHIND
	draw_line(*context, points[1], points[3]);
	//TOP RIGHT TO BOTTOM
	draw_line(*context, points[1], points[5]);
	//BOTTOM LEFT TO RIGHT
	draw_line(*context, points[4], points[5]);
	//BOTTOM LEFT TO BEHIND
	draw_line(*context, points[4], points[6]);
	//BACK BOTTOM LEFT TO RIGHT
	draw_line(*context, points[6], points[7]);
	//BOTTOM RIGHT TO BEHIND
	draw_line(*context, points[5], points[7]);
	//BACK RIGHT TO BOTTOM
	draw_line(*context, points[3], points[7]);

	
	mlx_put_image_to_window(context -> mlx, context -> win, context -> image, 0, 0);
	rotation+=0.1;
	usleep(50000);
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
	t_point *points = (t_point *)malloc(8 * sizeof(t_point));
	points[0] = (t_point){.x = 100, .y = 100, .z = 100};
	points[1] = (t_point){.x = 200, .y = 100, .z = 100}; 
	points[2] = (t_point){.x = 100, .y = 100, .z = 200};
	points[3] = (t_point){.x = 200, .y = 100, .z = 200};
	points[4] = (t_point){.x = 100, .y = 200, .z = 100};
	points[5] = (t_point){.x = 200, .y = 200, .z = 100};
	points[6] = (t_point){.x = 100, .y = 200, .z = 200};
	points[7] = (t_point){.x = 200, .y = 200, .z = 200};
	
	context.map =(t_map){.points = points, .rows=0, .cols=0};
	
	//DRAW IMAGE
		
	//ADD KEY HOOK
	mlx_key_hook(context.win, key_hook, &context);
	mlx_hook(context.win, ON_DESTROY, 0, destroy_hook, &context);
	mlx_loop_hook(context.mlx, loop_hook, &context);
	mlx_loop(context.mlx);
	return (0);
}


