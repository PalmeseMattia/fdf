/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rizz <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:05:56 by rizz              #+#    #+#             */
/*   Updated: 2024/05/18 12:05:59 by rizz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_node	*new_node(unsigned int content_size, char *content)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node -> next = NULL;
	if (content_size != 0)
	{
		node -> str = ft_calloc(content_size, sizeof(char));
		if (!node -> str)
		{
			free(node);
			return (NULL);
		}
		if (content != NULL && *content)
			ft_strlcpy(node -> str, content, content_size);
	}
	else
		node -> str = NULL;
	return (node);
}
