/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_conversion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:45:44 by dpalmese          #+#    #+#             */
/*   Updated: 2024/02/13 12:11:55 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_manage_conversion(char *conversion, va_list arguments)
{
	if (*conversion == 'c')
		return (ft_putchar_fd((char)va_arg(arguments, int), 1));
	else if (*conversion == 's')
		return (ft_putstr_fd(va_arg(arguments, char *), 1));
	else if (*conversion == 'd' || *conversion == 'i')
		return (ft_putnbrbase_fd(va_arg(arguments, int), 10, 1, 0));
	else if (*conversion == 'x')
		return (ft_putnbrbase_fd(va_arg(arguments, unsigned int), 16, 1, 0));
	else if (*conversion == 'X')
		return (ft_putnbrbase_fd(va_arg(arguments, unsigned int), 16, 1, 1));
	else if (*conversion == 'u')
		return (ft_putnbrbase_fd(va_arg(arguments, unsigned int), 10, 1, 0));
	else if (*conversion == 'p')
		return (ft_putpointer_fd(va_arg(arguments, void *), 1));
	else if (*conversion == '%')
		return (ft_putchar_fd('%', 1));
	return (0);
}
