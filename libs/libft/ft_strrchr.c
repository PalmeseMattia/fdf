/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 21:30:23 by dpalmese          #+#    #+#             */
/*   Updated: 2024/01/19 21:30:26 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
 * Like strchr() but in reverse
 */
char	*ft_strrchr(const char *s, int c)
{
	int	offset;

	offset = ft_strlen(s);
	while (offset >= 0)
	{
		if ((unsigned char)*(s + offset) == (unsigned char)c)
			return ((char *)(s + offset));
		offset--;
	}
	return (0);
}
