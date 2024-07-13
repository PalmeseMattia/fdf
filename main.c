#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

#define HEIGHT 1080
#define WIDTH 1920
#define ESC 65307
#define ON_DESTROY 17

typedef struct s_context
{
	void	*mlx;
	void	*win;
	void	*image;
	void	*pixels;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_context;


typedef struct s_image
{
	void	*image;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*pixels;
}	t_image;




int	key_hook(int keycode, t_context *context)
{
	printf("Key pressed: %d\n", keycode);
	if (keycode == ESC) {
       mlx_destroy_window(context -> mlx, context -> win);
		exit(EXIT_SUCCESS);
	}
	return 0;
}

int destroy_hook(t_context *context)
{
	exit(EXIT_SUCCESS);
}

int main()
{
	t_context context;
	int m[16] ={	1,1,1,1,
					1,2,2,1,
					1,2,2,1,
					1,1,1,1};
	int map_size = 16;
	int map_rows = 4;
	int map_cols = 4;

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
	int *map = (int *)malloc(16 * sizeof(int));
	for(int i = 0; i < 16; i++)
		map[i] = m[i];

	//FILL IMAGE
	//for(int y = 0; y < HEIGHT; y++) {
		int color = 0xFFFFFFFF;
		for(int x = 0; x < WIDTH; x++) {
			int byte_per_pixel = 4;
			int column = x * byte_per_pixel;
			int row = 100 * context.size_line;
			t_pixel pixel = get_pixel(context.pixels + row + column);
			*pixel.r = (color & 0xFF);
			*pixel.g = (color >> 8) & 0xFF;
			*pixel.b = (color >> 16) & 0xFF;
			*pixel.a = (color >> 24) & 0xFF;
		}
	//}

	//PRINT STUFF FROM THE IMAGE
	printf("BPP: %d\n", context.bits_per_pixel);
	printf("SIZE LINE: %d\n", context.size_line);
	printf("ENDIAN: %d\n", context.endian);

	//DRAW IMAGE
	mlx_put_image_to_window(context.mlx, context.win, context.image, 0, 0);
	
	//ADD KEY HOOK
	mlx_key_hook(context.win, key_hook, &context);
	mlx_hook(context.win, ON_DESTROY, 0, destroy_hook, &context);
	mlx_loop(context.mlx);
	return (0);
}


