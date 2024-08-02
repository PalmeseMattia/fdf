/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:39:23 by dpalmese          #+#    #+#             */
/*   Updated: 2024/01/30 10:36:17 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len + start > ft_strlen(s))
		len = ft_strlen(s + start);
	ret = (char *)ft_calloc(sizeof(char), (len + 1));
	if (ret == NULL)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len && s[i])
		{
			ret[j++] = s[i];
		}
		i++;
	}
	ret[j] = '\0';
	return (ret);
}
