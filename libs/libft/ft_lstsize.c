/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:19:07 by dpalmese          #+#    #+#             */
/*   Updated: 2024/01/21 16:19:10 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*current;

	if (lst != NULL)
	{
		i = 1;
		current = lst;
		while (current->next)
		{
			i++;
			current = current->next;
		}
		return (i);
	}
	return (0);
}
