/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:39:40 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/17 16:34:22 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	parse_textures(t_textures *textures, char *file_path)
{
	char	*line;
	int		fd;
	char	*trimmed_line;

	if (init_textures(textures) || file_path == NULL)
		return (perror("textures or file_path is NULL"), 1);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening texture file"), 1);
	line = get_next_line(fd);
	while (line)
	{
		trimmed_line = ft_strtrim(line, " \t");
		if (ft_strncmp(line, "NO", 2) == 0)
			textures->no = ft_strtrim(line + 2, " \t\n");
		else if (ft_strncmp(line, "so", 2) == 0)
			textures->so = ft_strtrim(line + 2, " \t\n");
		else if (ft_strncmp(line, "we", 2) == 0)
			textures->we = ft_strtrim(line + 2, " \t\n");
		else if (ft_strncmp(line, "ea", 2) == 0)
			textures->ea = ft_strtrim(line + 2, " \t\n");
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
	return (0);
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
	if (!textures->no || !textures->so || !textures->we || !textures->ea
		|| !textures->floor || !textures->ceiling)
	{
		destroy_textures(textures);
		return (perror("Missing texture paths"), 1);
	}
	return (0);
}

int	destroy_textures(t_textures *textures)
{
	if (textures == NULL)
		return (perror("textures is NULL"), 1);
	if (textures->no)
		free(textures->no);
	if (textures->so)
		free(textures->so);
	if (textures->we)
		free(textures->we);
	if (textures->ea)
		free(textures->ea);
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
