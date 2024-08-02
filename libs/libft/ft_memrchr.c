/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:34:40 by dpalmese          #+#    #+#             */
/*   Updated: 2024/01/08 12:34:58 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
 * The  memrchr()  function  is like the memchr() function, except that it
 * searches backward from the end of the n bytes pointed to by  s  instead
 * of forward from the beginning.
 */
void	*ft_memrchr(const void *s, int c, size_t n)
{
	unsigned char	*src;

	if (n != 0)
	{
		src = (unsigned char *)s + n;
		while (--n != 0)
		{
			if ((unsigned char)*src == (unsigned char)c)
			{
				return ((void *)(src));
			}
			src--;
		}
	}
	return (NULL);
}
