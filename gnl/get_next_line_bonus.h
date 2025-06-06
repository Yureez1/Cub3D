/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:52:48 by jbanchon          #+#    #+#             */
/*   Updated: 2024/07/02 12:04:41 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# ifndef FD_MAX_SIZE
#  define FD_MAX_SIZE 1024
# endif

# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_fill_buffer(int fd, char *buf, char *stash);
char	*ft_define_line(char *line_buf);
char	*ft_substr(const char *s, size_t start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
void	free_stash(void) __attribute__((destructor));

#endif