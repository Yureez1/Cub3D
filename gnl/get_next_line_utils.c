/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:57:54 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/06 15:57:57 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// TO EXTRACT A SUB STRING
char	*ft_substr(const char *s, size_t start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	substrlen;

	if (s == NULL)
		return (NULL);
	substrlen = ft_strlen(s);
	if (start >= substrlen)
		return (ft_strdup(""));
	if (start + len > substrlen)
		len = substrlen - start;
	i = 0;
	substr = (char *)malloc(sizeof(char) * len + 1);
	if (substr == NULL)
		return (NULL);
	while (i < len && s[start + i] != '\0')
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
// TO CHECK THE '\N'

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
// TO COPY THE STRING READ

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;
	int		strlen;

	i = 0;
	strlen = ft_strlen(src);
	dest = malloc(sizeof(char) * (strlen + 1));
	if (dest == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
// TO CONCATENATE THE DIFFERENTS STRINGS/CHARACTER READ

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*len_final;
	int		size;
	int		i;
	int		j;

	size = ft_strlen(s1) + ft_strlen(s2);
	len_final = (char *)malloc(sizeof(char) * (size + 1));
	if (len_final == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		len_final[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		len_final[i] = s2[j];
		i++;
		j++;
	}
	len_final[i] = '\0';
	return (len_final);
}
// CHECK THE LENGTH TO MALLOC

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
