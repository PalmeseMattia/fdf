/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rizz <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:05:26 by rizz              #+#    #+#             */
/*   Updated: 2024/10/05 08:22:48 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*get_next_line(int fd)
{
	t_node		*list;
	char		*result;
	static char	*buffer = NULL;

	list = NULL;
	if (fd < 0)
		return (NULL);
	if (!buffer)
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	create_list(fd, &list, buffer);
	if (!list)
	{
		if (buffer)
			free(buffer);
		buffer = NULL;
		return (NULL);
	}
	result = join_list(&list, buffer);
	free_list(list);
	return (result);
}

/*
 * Create a linked list with the reads from the file descriptor,
 * until a newline or eof character is found
 */
void	create_list(int fd, t_node **list, char *bf)
{
	char	*buffer;
	t_node	*node;
	int		chars;

	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (ft_strlen(bf) > 0)
		chars = ft_strlcpy(buffer, bf, ft_strlen(bf) + 1);
	else
		chars = read(fd, buffer, BUFFER_SIZE);
	while (chars > 0)
	{
		node = new_node(chars + 1, buffer);
		lstadd_back(list, node);
		if (ft_strchr(buffer, '\n') || ft_strchr(buffer, EOF))
			break ;
		chars = read(fd, buffer, BUFFER_SIZE);
	}
	while (*bf)
	{
		*bf = 0;
		bf++;
	}
	free(buffer);
}

/*
 * Calculate the size of the string composed by the nodes of the list,
 * then alloc and write the result string.
 * Measure, alloc and write :)
 */
char	*join_list(t_node **list, char *buffer)
{
	char	*res;
	int		res_len;
	t_node	*node;
	int		off;

	res_len = 0;
	off = 0;
	node = *list;
	while (node)
	{
		res_len += ft_strlen(node -> str);
		node = node -> next;
	}
	node = *list;
	res = ft_calloc(res_len + 1, sizeof(char));
	while (node)
	{
		off += ft_strlcpy(res + off, node -> str, ft_strlen(node -> str) + 1);
		node = node -> next;
	}
	split_result(res, buffer);
	return (res);
}

t_node	*lstadd_back(t_node **head, t_node *new_node)
{
	t_node	*last;

	if (!new_node)
		return (NULL);
	if (!(*head))
		*head = new_node;
	else
	{
		last = *head;
		while (last -> next)
			last = last -> next;
		last -> next = new_node;
	}
	return (new_node);
}

void	split_result(char *line, char *buffer)
{
	char	*nl;

	nl = ft_strchr(line, '\n');
	if (nl)
	{
		if (buffer)
			ft_strlcpy(buffer, nl + 1, (nl + 1) - buffer);
		*(nl + 1) = '\0';
	}
}
