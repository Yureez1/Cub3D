/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:21:46 by leaugust          #+#    #+#             */
/*   Updated: 2025/07/15 14:23:57 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*allocate_and_check(const char *s1, const char *s2)
{
	char	*dest;
	int		size;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	return (dest);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	int		i;
	int		j;

	res = allocate_and_check(s1, s2);
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

char	*ft_define_line(char *line_buf)
{
	size_t	i;
	char	*stash;

	i = 0;
	while (line_buf[i] != '\n' && line_buf[i])
		i++;
	if (line_buf[i] == '\0')
		return (NULL);
	stash = ft_substr(line_buf, i + 1, ft_strlen(line_buf) - (i + 1));
	if (!stash || *stash == '\0')
	{
		free(stash);
		stash = NULL;
	}
	line_buf[i + 1] = '\0';
	return (stash);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
