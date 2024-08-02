/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:27:58 by dpalmese          #+#    #+#             */
/*   Updated: 2024/01/08 18:08:37 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
 * Copy first n bytes to destination. 
 * Memory may overlap, as though the bytes in src are first copied
 * in memory that does not overlap src or dest. 
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*from;
	unsigned char	*to;
	int				i;

	from = (unsigned char *)src;
	to = (unsigned char *)dest;
	if (from == to || n == 0)
		return (dest);
	else if (to > from && to - from < (int)n)
	{
		i = n - 1;
		while (i >= 0)
		{
			to[i] = from[i];
			i--;
		}
		return (dest);
	}
	else
	{
		ft_memcpy(dest, src, n);
		return (dest);
	}
}
