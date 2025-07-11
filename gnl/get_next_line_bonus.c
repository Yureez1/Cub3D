/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:00:29 by jbanchon          #+#    #+#             */
/*   Updated: 2024/07/02 12:39:12 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_stash(void)
{
	get_next_line(-23);
}

char	*get_next_line(int fd)
{
	static char	*stash[FD_MAX_SIZE];
	char		*line;
	char		*buf;

	if (fd < 0 || fd >= FD_MAX_SIZE || BUFFER_SIZE <= 0)
	{
		if (stash[fd])
			free(stash[fd]);
		return (NULL);
	}
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf || read(fd, buf, 0) < 0)
	{
		free(stash[fd]);
		free(buf);
		stash[fd] = NULL;
		return (NULL);
	}
	line = ft_fill_buffer(fd, stash[fd], buf);
	free(buf);
	if (!line)
		return (NULL);
	stash[fd] = ft_define_line(line);
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
			return (stash);
			return (NULL);
		}
		if (read_bytes == 0)
			return (stash);
		buf[read_bytes] = '\0';
		if (!stash)
			stash = ft_strdup("");
		temp = stash;
		stash = ft_strjoin(temp, buf);
		free(temp);
		if (ft_strchr(buf, '\n'))
			return (stash);
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
	stash = ft_substr(line_buf, i + 1, ft_strlen(line_buf));
	if (!stash)
		return (NULL);
	if (*stash == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line_buf[i + 1] = '\0';
	return (stash);
}
