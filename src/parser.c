/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <dpalmese@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:34:20 by dpalmese          #+#    #+#             */
/*   Updated: 2024/08/16 11:41:32 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/fdf.h"
#define C 0xFFFFFFFF
/**
 * Parse a map from a .fdf file
 * We assume that the file is correctly formatted, meaning that:
 * - Every line has the same number of elements.
 * - The elements are numerical values separated only by whitespaces.
 * - There is at least one line.
 */
void	parse_map(int fd, t_map *m)
{
	char	**v;
	char	*line;
	int		i;
	int		j;
	t_point	p;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		j = 0;
		v = ft_split(line, ' ');
		while (*(v + j) != NULL)
		{
			p = new_point(i % m -> cols, i / m -> cols, ft_atoi(*(v + j)), C);
			m -> points[i++] = p;
			free(*(v + j++));
		}
		free(line);
		line = get_next_line(fd);
		free(v);
	}
}

void	get_map_size(int fd, int *rows, int *cols)
{
	char	*line;
	char	**values;
	int		i;

	i = 0;
	line = get_next_line(fd);
	values = ft_split(line, ' ');
	while (values[i])
	{
		*cols += 1;
		free(values[i++]);
	}
	*rows += 1;
	free(values);
	free(line);
	line = get_next_line(fd);
	while (line)
	{
		*rows += 1;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}
