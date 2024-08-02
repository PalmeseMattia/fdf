/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:54:21 by dpalmese          #+#    #+#             */
/*   Updated: 2024/02/12 13:12:25 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
 * Write the address pointed by p to the file descriptor fd,
 * returning the number of characters printed.
 */
int	ft_putpointer_fd(void *p, int fd)
{
	uintptr_t			p_intvalue;
	int					i;
	int					result;
	unsigned char		byte;

	if (!p)
		return (ft_putstr_fd("0x0", fd));
	result = 0;
	i = (sizeof(p) * 2) - 1;
	p_intvalue = (uintptr_t) p;
	result += ft_putstr_fd("0x", fd);
	byte = (p_intvalue >> (i * 4) & 0xF);
	while (i >= 0 && byte == 0)
	{
		i--;
		byte = (p_intvalue >> (i * 4) & 0xF);
	}
	while (i >= 0)
	{
		byte = (p_intvalue >> (i * 4) & 0xF);
		result += ft_putnbrbase_fd((long)byte, 16, 1, 0);
		i--;
	}
	return (result);
}
