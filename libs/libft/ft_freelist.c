/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freelist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <dpalmese@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 08:21:08 by dpalmese          #+#    #+#             */
/*   Updated: 2024/10/05 08:21:12 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	free_list(t_node *list)
{
	t_node	*next;

	while (list)
	{
		next = list->next;
		if (list -> str)
			free(list->str);
		free(list);
		list = next;
	}
}
