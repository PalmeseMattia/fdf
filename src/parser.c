/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <dpalmese@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:34:20 by dpalmese          #+#    #+#             */
/*   Updated: 2024/08/15 15:34:07 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/fdf.h"
/**
 * Parse a map from a .fdf file
 * We assume that the file is correctly formatted, meaning that:
 * - Every line has the same number of elements.
 * - The elements are numerical values separated only by whitespaces.
 * - There is at least one line.
 */
void	parse_map(char *filename, t_context *context)
{
	char	**values;
	char	*line;
	t_map	map;
	int	fd;
	int	i;

	i = 0;
	map = context -> map;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		values = ft_split(line, ' ');
		char **tmp = values;
		while (*values)
		{
			t_point point = new_point(i % map.cols, i / map.cols, ft_atoi(*values), 0xFFFFFFFF);
			context -> map.points[i++] = point;
			free(*(values));
			values++;
		}
		free(tmp);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}


void get_map_size(char *filename, int *rows, int *cols)
{
	char	*line;
	char	**values;
	int	 fd;
	int	 i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error while opening file!");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	if (line != NULL)
	{
		i = 0;
		values = ft_split(line, ' ');
		while (values[i] != NULL)
		{
			*cols += 1;
			free(values[i]);
			i++;
		}
		*rows += 1;
		free(values);
		free(line);
	}
	line = get_next_line(fd);
	while ((line))
	{
		*rows += 1;
		line = get_next_line(fd);
		free(line);
	}
	free(line);
	close(fd);
}
