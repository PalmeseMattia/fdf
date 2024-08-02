/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:32:41 by dpalmese          #+#    #+#             */
/*   Updated: 2024/01/23 15:32:45 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	ft_aux(long int num, int fd)
{
	int	w;

	if (num > 9)
		ft_aux(num / 10, fd);
	w = (num % 10) + '0';
	ft_putchar_fd(w, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	num;

	if (fd < 0)
		return ;
	num = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		num = -num;
	}
	ft_aux(num, fd);
}
