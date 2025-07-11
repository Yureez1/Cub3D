/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texpath.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:12:44 by leaugust          #+#    #+#             */
/*   Updated: 2025/06/27 14:02:40 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	parse_textures_colors(t_texpath *texpath, char *file_path)
{
	int		fd;
	char	*line;

	if (texpath == NULL || file_path == NULL)
		return (printf("texpath or file_path is NULL"), 1);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (printf("Error : Cannot open color file"), 1);
	line = get_next_line(fd);
	while (line)
	{
		if (parse_line(texpath, line))
		{
			free(line);
			close(fd);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (check_textures(texpath))
		return (close(fd), 1);
	return (close(fd), 0);
}

int	parse_line(t_texpath *texpath, char *line)
{
	char	*trimmed_line;
	int		ret;

	trimmed_line = ft_strtrim(line, " \t\n");
	ret = 0;
	if (!trimmed_line || trimmed_line[0] == '\0')
		return (free(trimmed_line), 0);
	ret = handle_texture_line(texpath, trimmed_line);
	if (ret != 0)
		return (free(trimmed_line), ret);
	ret = handle_color_line(texpath, trimmed_line);
	if (ret != 0)
		return (free(trimmed_line), ret);
	return (free(trimmed_line), 0);
}

int	handle_texture_line(t_texpath *texpath, char *line)
{
	if (!ft_strncmp(line, "NO", 2))
	{
		if (texpath->no)
			return (printf("Error: Duplicate NO\n"), 1);
		texpath->no = ft_strtrim(line + 2, " \t\n");
	}
	else if (!ft_strncmp(line, "SO", 2))
	{
		if (texpath->so)
			return (printf("Error: Duplicate SO\n"), 1);
		texpath->so = ft_strtrim(line + 2, " \t\n");
	}
	else if (!ft_strncmp(line, "WE", 2))
	{
		if (texpath->we)
			return (printf("Error: Duplicate WE\n"), 1);
		texpath->we = ft_strtrim(line + 2, " \t\n");
	}
	else if (!ft_strncmp(line, "EA", 2))
	{
		if (texpath->ea)
			return (printf("Error: Duplicate EA\n"), 1);
		texpath->ea = ft_strtrim(line + 2, " \t\n");
	}
	return (0);
}

int	handle_color_line(t_texpath *texpath, char *line)
{
	if (!ft_strncmp(line, "F ", 2))
		return (handle_floor(texpath, line));
	if (!ft_strncmp(line, "C ", 2))
		return (handle_ceiling(texpath, line));
	return (0);
}
