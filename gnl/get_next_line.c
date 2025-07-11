/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:57:17 by jbanchon          #+#    #+#             */
/*   Updated: 2025/07/11 17:50:21 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_stash(void)
{
	get_next_line(-23);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buf;
	char		*line;

	if (fd < -0 || BUFFER_SIZE <= 0)
	{
		if (stash)
			free(stash);
		stash = NULL;
		return (NULL);
	}
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf || read(fd, buf, 0) < 0)
	{
		free(stash);
		free(buf);
		stash = NULL;
		return (NULL);
	}
	line = ft_fill_buffer(fd, stash, buf);
	free(buf);
	if (!line)
	{
		free(stash);
		return (NULL);
	}
	stash = ft_define_line(line);
	return (line);
}

// FONCTION QUI LIT LE FICHIER
char	*ft_fill_buffer(int fd, char *stash, char *buf)
{
	int		read_bytes;
	char	*temp;

	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(stash);
			return (NULL);
		}
		else if (read_bytes == 0)
			break ;
		buf[read_bytes] = '\0';
		if (!stash)
			stash = ft_strdup("");
		if (!stash)
			return (NULL);
		temp = stash;
		stash = ft_strjoin(temp, buf);
		free(temp);
		if (!stash)
			return (NULL);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (stash);
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
