/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:05:09 by dpalmese          #+#    #+#             */
/*   Updated: 2024/10/05 08:22:04 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>
# include <stdio.h>
# include <fcntl.h>

# define ASCII_ZERO 48
# define CHAR_SIZE 1
#  ifndef BUFFER_SIZE
#   define BUFFER_SIZE 42
#  endif

typedef struct s_list
{
	void		*content;
	struct s_list	*next;
}	t_list;
typedef struct s_node
{
	char			*str;
	struct s_node	*next;
}	t_node;
char		*get_next_line(int fd);
t_node		*new_node(unsigned int content_size, char *content);
void		create_list(int fd, t_node **list, char *buffer);
t_node		*lstadd_back(t_node **head, t_node *new_node);
char		*join_list(t_node **list, char *buffer);
void		split_result(char *line, char *buffer);
int		ft_printf(const char *format, ...);
int		ft_manage_conversion(char *conversion, va_list arguments);
void		*ft_memset(void *ptr, int value, size_t n);
void		ft_bzero(void *ptr, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memccpy(void *dest, const void *src, int c, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memrchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t		ft_strlen(const char *s);
size_t		ft_strnlen(const char *s, size_t maxlen);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
unsigned int	ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *nptr);
int		ft_isupper(int c);
int		ft_islower(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strdup(const char *s);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_putchar_fd(char c, int fd);
size_t		ft_putstr_fd(char *s, int fd);
size_t		ft_putendl_fd(char *s, int fd);
void		ft_strrev(char *str);
char		*ft_strjoin(const char *s1, const char *s2);
int		ft_numdigits(int n);
char		*ft_strncpy(char *dst, const char *src, size_t len);
char		*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char		*ft_itoa(int n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strtrim(char const *s1, char const *set);
void		ft_putnbr_fd(int n, int fd);
char		**ft_split(char const *s, char c);
size_t		ft_putnstr_fd(char *s, int len, int fd);
int		ft_putpointer_fd(void *p, int fd);
int		ft_putnbrbase_fd(long number, int base, int fd, int capital);
void	free_list(t_node *list);
#endif
