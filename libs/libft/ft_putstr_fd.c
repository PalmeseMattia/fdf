/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:30:24 by dpalmese          #+#    #+#             */
/*   Updated: 2024/02/12 12:38:46 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_putstr_fd(char *s, int fd)
{
	int	size;

	if (fd < 0)
		return (0);
	if (s == NULL)
		return (write(fd, "(null)", 6));
	size = ft_strlen(s);
	return (write(fd, s, size));
}
