/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:17:59 by jbanchon          #+#    #+#             */
/*   Updated: 2025/07/16 15:58:57 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_parts(char const *s, char delim)
{
	int	count;
	int	i;

	if (!s)
		return (0);
	count = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] == delim)
			count++;
		i++;
	}
	return (count);
}

static char	**free_split(char **words)
{
	int	i;

	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
		free(words[i++]);
	free(words);
	return (NULL);
}

static char	*ft_extract_part(char const *s, int start, int end)
{
	char	*part;
	int		i;

	part = malloc(end - start + 1);
	if (!part)
		return (NULL);
	i = 0;
	while (start < end)
		part[i++] = s[start++];
	part[i] = '\0';
	return (part);
}

static int	fill_split(char **res, char const *s, char c)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			res[j] = ft_extract_part(s, start, i);
			if (!res[j])
				return (0);
			j++;
			start = i + 1;
		}
		i++;
	}
	res[j] = ft_extract_part(s, start, i);
	if (!res[j])
		return (0);
	res[++j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**res;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (ft_count_parts(s, c) + 1));
	if (!res)
		return (NULL);
	if (!fill_split(res, s, c))
		return (free_split(res));
	return (res);
}
