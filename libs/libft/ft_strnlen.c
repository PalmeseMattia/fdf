/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:44:07 by dpalmese          #+#    #+#             */
/*   Updated: 2024/01/25 10:44:10 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
 * The strnlen() function determines the length of a fixed-size string.
 * It returns strlen(s), if that is less than maxlen,  or  maxlen  if
 * there is no null terminating ('\0') among the first maxlen 
 * characters pointed to by s.
 */
size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	while (len < maxlen && *s)
	{
		len++;
		s++;
	}
	return (len);
}
