/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:01:43 by dpalmese          #+#    #+#             */
/*   Updated: 2024/01/08 16:03:20 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
	{
		return (0);
	}
	while ((*s1 && *s2 && (*s1 == *s2)) && n > 1)
	{
		s1++;
		s2++;
		n--;
	}
	return (*(const unsigned char *) s1 - *(const unsigned char *) s2);
}
