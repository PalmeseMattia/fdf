/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:44:10 by dpalmese          #+#    #+#             */
/*   Updated: 2024/01/08 14:43:31 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
 * The strlcpy() and strlcat() functions copy and 
 * concatenate strings respectively.
 * Note that a byte for the NULL should be included in size.
 * Android style
 */
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = -1;
	while (src[++i] && (i + 1) < size)
		dest[i] = src[i];
	if (size)
		dest[i] = '\0';
	return (ft_strlen(src));
}
