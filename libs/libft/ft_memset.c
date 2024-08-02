/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:35:37 by dpalmese          #+#    #+#             */
/*   Updated: 2024/01/08 12:35:45 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
 * Fill memory with a constant byte.
 * returning a pointer to void is useful when we don't know the type
 * of the pointer.
 */
void	*ft_memset(void *ptr, int value, size_t n)
{
	unsigned char	*p;

	p = ptr;
	while (n--)
	{
		*p++ = (unsigned char)value;
	}
	return (ptr);
}
