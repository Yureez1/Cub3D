/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:57:17 by jbanchon          #+#    #+#             */
/*   Updated: 2025/07/15 14:24:35 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_stash(void)
{
	get_next_line(-23);
}

static int	is_invalid(int fd, char **stash, char *buf)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buf, 0) < 0)
	{
		free(buf);
		if (*stash)
			free(*stash);
		*stash = NULL;
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buf;
	char		*line;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	if (is_invalid(fd, &stash, buf))
		return (NULL);
	line = ft_fill_buffer(fd, stash, buf);
	free(buf);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	stash = ft_define_line(line);
	return (line);
}

static char	*append_to_stash(char *stash, char *buf)
{
	char	*temp;

	if (!stash)
		stash = ft_strdup("");
	if (!stash)
		return (NULL);
	temp = stash;
	stash = ft_strjoin(temp, buf);
	free(temp);
	return (stash);
}

char	*ft_fill_buffer(int fd, char *stash, char *buf)
{
	int	read_bytes;

	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(stash), NULL);
		if (read_bytes == 0)
			break ;
		buf[read_bytes] = '\0';
		stash = append_to_stash(stash, buf);
		if (!stash)
			return (NULL);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (stash);
}
