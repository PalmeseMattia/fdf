/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:29:09 by dpalmese          #+#    #+#             */
/*   Updated: 2024/01/21 16:30:09 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_putendl_fd(char *s, int fd)
{
	size_t	size;

	if (fd < 0)
		return (0);
	size = ft_strlen(s);
	write(fd, s, size);
	write(fd, "\n", 1);
	return (size + 1);
}
