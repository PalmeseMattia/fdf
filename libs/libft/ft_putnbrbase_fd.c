/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:03:53 by dpalmese          #+#    #+#             */
/*   Updated: 2024/02/12 13:05:39 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_putnbrbase_fd(long number, int base, int fd, int capital)
{
	char	*digits;
	int		result;

	result = 0;
	if (capital)
		digits = "0123456789ABCDEF";
	else
		digits = "0123456789abcdef";
	if (fd < 0)
		return (0);
	if (base < 2 || base > 16)
		return (0);
	if (number < 0 && base == 10)
	{
		result += ft_putchar_fd('-', fd);
		number = -number;
	}
	if (number < base)
	{
		result += ft_putchar_fd(digits[number], fd);
		return (result);
	}
	result += ft_putnbrbase_fd(number / base, base, fd, capital);
	result += ft_putchar_fd(digits[number % base], fd);
	return (result);
}
