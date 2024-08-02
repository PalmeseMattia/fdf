/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 21:46:47 by dpalmese          #+#    #+#             */
/*   Updated: 2024/01/19 21:46:51 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*src;
	unsigned int	i;

	i = 0;
	src = ft_strdup(s);
	if (!src)
		return (NULL);
	while (src[i])
	{
		src[i] = f(i, s[i]);
		i++;
	}
	return (src);
}
