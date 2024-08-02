/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:47:50 by dpalmese          #+#    #+#             */
/*   Updated: 2024/02/13 12:11:47 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	arguments;
	int		chars_printed;
	char	*next_stop;

	chars_printed = 0;
	va_start(arguments, format);
	next_stop = ft_strchr(format, '%');
	while (next_stop != NULL)
	{
		chars_printed += ft_putnstr_fd((char *)format, next_stop - format, 1);
		chars_printed += ft_manage_conversion(next_stop + CHAR_SIZE, arguments);
		format = next_stop + (2 * CHAR_SIZE);
		next_stop = ft_strchr(format, '%');
	}
	chars_printed += ft_putstr_fd((char *)format, 1);
	va_end(arguments);
	return (chars_printed);
}
