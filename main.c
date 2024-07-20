#include "fdf.h"

#define HEIGHT 1080
#define WIDTH 1920
#define ESC 65307
#define ON_DESTROY 17

typedef struct s_point
{
	int x;
	int y;
	int z;
}	t_point;

typedef struct s_context
{
	void	*mlx;
	void	*win;
	void	*image;
	void	*pixels;
	int	bits_per_pixel;
	int	size_line;
	int	endian;
}	t_context;

typedef struct s_image
{
	void	*image;
	int	bits_per_pixel;
	int	size_line;
	int	endian;
	char	*pixels;
}	t_image;

typedef struct s_map
{
	t_point	*points;
	int	rows;
	int	cols;
}	t_map;

void draw_pixel(t_context context, t_point point, int color)
{
	if (point.x < WIDTH && point.x > 0 && point.y < HEIGHT && point.y > 0)
	{
		int byte_per_pixel = 4;
		int column = (point.x * byte_per_pixel);
		int row = (point.y * context.size_line);

		t_pixel pixel = get_pixel(context.pixels + row + column);
		*pixel.a =	(color >> 24)	& 0xFF;
		*pixel.r =	(color >> 16)	& 0xFF;
		*pixel.g =	(color >> 8)	& 0xFF;
		*pixel.b =	color		& 0xFF;
	}
}

void draw_line(t_context context, t_point point0, t_point point1)
{
	int dx = abs(point1.x - point0.x);
	int sx = point0.x < point1.x ? 1 : -1;
	int dy = -abs(point1.y - point0.y);
	int sy = point0.y < point1.y ? 1 : -1;
	int error = dx + dy;
	
	while (1)
	{
		draw_pixel(context, point0, 0xFFFFFFFF); //TODO: implement plot
		if (point0.x == point1.x && point0.y == point1.y)
			break ;
		int e2 = 2 * error;
		if (e2 >= dy)
		{
			if (point0.x == point1.x) 
				break ;
			error = error + dy;
			point0.x = point0.x + sx;
		}
		if (e2 <= dx)
		{
			if (point0.y == point1.y)
				break ;
			error = error + dx;
			point0.y = point0.y + sy;
		}
	}
}


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
	static t_point point0 = {.x = 0, .y = 0, .z = 0};
	t_point point1 = {.x = WIDTH, .y = HEIGHT, .z = 0};
	draw_line(*context, point0, point1);
	mlx_put_image_to_window(context -> mlx, context -> win, context -> image, 0, 0);
	point0.x++;
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
		points[i] = (t_point){i % map_cols, i / map_rows ,m[i]};
	}
	t_map map = {.points = points, .rows = 4, .cols = 4};
	
	//ITERATE MAP AND DRAW POINTS
	for (int i = 0; i < map_size; i++) {
		t_point point = map.points[i];
		printf("X: %d, Y: %d, Z: %d\n", point.x, point.y, point.z);
		draw_pixel(context, point, 0xFFFFFFFF);
	}


	//PRINT STUFF FROM THE IMAGE
	printf("BPP: %d\n", context.bits_per_pixel);
	printf("SIZE LINE: %d\n", context.size_line);
	printf("ENDIAN: %d\n", context.endian);

	//DRAW IMAGE
	mlx_put_image_to_window(context.mlx, context.win, context.image, 0, 0);
	
	//ADD KEY HOOK
	mlx_key_hook(context.win, key_hook, &context);
	mlx_hook(context.win, ON_DESTROY, 0, destroy_hook, &context);
	mlx_loop_hook(context.mlx, loop_hook, &context);
	mlx_loop(context.mlx);
	return (0);
}


