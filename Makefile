CC = cc

DEBUG_FLAGS = -g
FLAGS = $(DEBUG_FLAGS) #-Wall -Wextra -Werror

SRCS = src/main.c src/draw_utils.c src/rotations.c src/parser.c src/point.c src/bresenham.c
OBJS = $(SRCS:.c=.o)

EXEC = fdf

MLX_LIB = mlx_Linux

LIBFT_DIR= libs/libft
LIBFT = ft


all : $(LIBFT) $(EXEC)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(EXEC) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -L$(LIBFT_DIR) -l$(LIBFT) -Lmlx_linux -l$(MLX_LIB) -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(EXEC)
%.o: %.c
	$(CC) $(FLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

debug : FLAGS += $(DEBUG_FLAGS)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(EXEC)

re : fclean all

.PHONY: all clean fclean re
