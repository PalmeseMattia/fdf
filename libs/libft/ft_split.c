/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:48:58 by dpalmese          #+#    #+#             */
/*   Updated: 2024/01/25 10:49:01 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static void	new_string(const char *str, int start, int end, char *dest)
{
	int	i;

	i = 0;
	while (i < end)
	{
		dest[i] = str[start + i];
		i++;
	}
	dest[i] = '\0';
}

static void	aux(char **arr, const char *str, char c)
{
	int	i;
	int	j;
	int	z;

	i = 0;
	z = 0;
	while (str[i] && z <= count_words(str, c))
	{
		if (str[i] == c)
			i++;
		else
		{
			j = 0;
			while (str[i + j] != c && str[i + j])
				j++;
			arr[z] = (char *)malloc(sizeof(char) * (j + 1));
			if (!arr[z])
				return ;
			new_string(str, i, j, arr[z]);
			z++;
			i += j;
		}
	}
}

char	**ft_split(const char *str, char c)
{
	char	**arr;
	int		n_words;

	if (!str)
		return (NULL);
	n_words = count_words(str, c);
	arr = ft_calloc(n_words + 1, sizeof(char *));
	arr[n_words] = NULL;
	if (!arr)
		return (NULL);
	aux(arr, str, c);
	return (arr);
}
