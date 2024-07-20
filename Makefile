CC = cc

FLAGS = #-Wall -Wextra -Werror
DEBUG_FLAGS = -g

SRCS = cube.c draw_utils.c
OBJS = $(SRCS:.c=.o)

EXEC = fdf

MLX_LIB = mlx_Linux

all : $(EXEC)

$(EXEC) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -Lmlx_linux -l$(MLX_LIB) -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(EXEC)
%.o: %.c
	$(CC) $(FLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

debug : FLAGS += $(DEBUG_FLAGS)
debug : clean $(EXEC)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(EXEC)

re : fclean all

.PHONY: all clean fclean re
