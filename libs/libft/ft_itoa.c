/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:59:24 by dpalmese          #+#    #+#             */
/*   Updated: 2024/01/19 11:59:27 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/**
 * Measure, allocate and write :)
*/
char	*ft_itoa(int n)
{
	char	*result;
	int		num_size;

	num_size = ft_numdigits(n);
	result = ft_calloc(num_size + 1, sizeof(char));
	if (!result)
		return (NULL);
	result[num_size] = '\0';
	if (n < 0)
		result[0] = '-';
	else if (n < 10 && n >= 0)
	{
		result[0] = n + ASCII_ZERO;
		return (result);
	}
	while (--num_size >= 0 && n)
	{
		if (n < 0)
			result[num_size] = (-(n % 10)) + ASCII_ZERO;
		else
			result[num_size] = (n % 10) + ASCII_ZERO;
		n /= 10;
	}
	return (result);
}
