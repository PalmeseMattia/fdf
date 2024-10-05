CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

NAME = libft.a

SRC =	ft_putchar_fd.c ft_atoi.c ft_putendl_fd.c \
		ft_bzero.c ft_putnbr_fd.c ft_calloc.c \
		ft_putstr_fd.c ft_isalnum.c ft_split.c \
		ft_isalpha.c ft_strchr.c ft_isascii.c \
		ft_strcmp.c ft_isdigit.c ft_strdup.c \
		ft_islower.c ft_striteri.c ft_isprint.c \
		ft_strjoin.c ft_isupper.c ft_strlcat.c \
		ft_itoa.c ft_strlcpy.c ft_strlen.c \
		ft_strmapi.c ft_strncmp.c ft_strncpy.c \
		ft_strnlen.c ft_strnstr.c ft_strrchr.c \
		ft_strrev.c ft_strtrim.c ft_memchr.c \
		ft_substr.c ft_memcmp.c ft_tolower.c \
		ft_memcpy.c ft_toupper.c ft_memmove.c \
		ft_memrchr.c ft_memset.c ft_numdigits.c \
		ft_putnstr_fd.c ft_putnbrbase_fd.c ft_putpointer_fd.c \
		ft_manage_conversion.c ft_printf.c get_next_line.c \
		get_next_line_utils.c ft_freelist.c

BSRCS =	ft_lstdelone.c ft_lstadd_front.c ft_lstadd_back.c \
		ft_lstclear.c ft_lstnew.c ft_lstlast.c \
		ft_lstiter.c ft_lstmap.c ft_lstsize.c\

OBJS = $(SRC:.c=.o)

BOBJS = $(BSRCS:.c=.o)

HEADER = libft.h

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) -r $@ $?

bonus: $(OBJS) $(BOBJS)
	$(AR) -r $(NAME) $?

%.o: %.c
	$(CC) -c $(CFLAGS) $?

clean:
	rm -rf $(OBJS) $(BOBJS)

fclean: clean
	rm -f $(NAME) bonus

re : fclean all

.PHONY: all bonus clean fclean re
