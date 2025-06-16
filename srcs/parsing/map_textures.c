/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:39:40 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/14 22:08:33 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	init_textures(t_textures *textures)
{
	textures->no = NULL;
	textures->so = NULL;
	textures->we = NULL;
	textures->ea = NULL;
	textures->floor = NULL;
	textures->ceiling = NULL;
	return (0);
}

int	parse_textures(t_textures *textures, char *file_path)
{
	char	*line;
	int		fd;

	if (init_textures(textures) || file_path == NULL)
		return (perror("textures or file_path is NULL"), 1);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening texture file"), 1);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "NO", 3) == 0)
			textures->no = ft_strtrim(line + 3, " \n");
		else if (ft_strncmp(line, "SO", 3) == 0)
			textures->so = ft_strtrim(line + 3, " \n");
		else if (ft_strncmp(line, "WE", 3) == 0)
			textures->we = ft_strtrim(line + 3, " \n");
		else if (ft_strncmp(line, "EA", 3) == 0)
			textures->ea = ft_strtrim(line + 3, " \n");
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 0);
}

int	handle_color_line(t_textures *textures, char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		textures->floor = ft_strtrim(line + 2, " \n");
		if (!textures->floor)
			return (perror("Failed to allocate memory : floor color"), 1);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		textures->ceiling = ft_strtrim(line + 2, " \n");
		if (!textures->ceiling)
			return (perror("Failed to allocate memory : ceiling color"), 1);
	}
}

int	parse_color(t_textures *textures, char *file_path)
{
	int		fd;
	char	*line;

	if (textures == NULL || file_path == NULL)
		return (perror("textures or file_path is NULL"), 1);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening color file"), 1);
	line = get_next_line(fd);
	while (line)
	{
		if (handle_color_line(textures, line))
		{
			free(line);
			close(fd);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 0);
}

int	parse_textures_colors(t_textures *textures, char *file_path)
{
	if (parse_textures(textures, file_path) || parse_color(textures, file_path))
	{
		destroy_textures(textures);
		return (perror("Failed to parse textures or colors"), 1);
	}
	return (0);
}

int	destroy_textures(t_textures *textures)
{
	if (textures == NULL)
		return (perror("textures is NULL"), 1);
	if (textures->NO)
		free(textures->NO);
	if (textures->SO)
		free(textures->SO);
	if (textures->WE)
		free(textures->WE);
	if (textures->EA)
		free(textures->EA);
	if (textures->floor)
		free(textures->floor);
	if (textures->ceiling)
		free(textures->ceiling);
	return (0);
}

int	convert_rgb(unsigned int r, unsigned int g, unsigned int b)
{
	if (r > 255 || g > 255 || b > 255)
		return (perror("RGB values must be between 0 and 255"), -1);
	return ((r << 16) | (g << 8) | b);
}
