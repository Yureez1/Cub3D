/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:39:40 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/18 13:52:58 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	handle_texture_line(t_textures *textures, char *line)
{
	if (!ft_strncmp(line, "NO", 2))
	{
		if (textures->no)
			return (perror("Duplicate NO"), 1);
		textures->no = ft_strtrim(line + 2, " \t\n");
	}
	else if (!ft_strncmp(line, "SO", 2))
	{
		if (textures->so)
			return (perror("Duplicate SO"), 1);
		textures->so = ft_strtrim(line + 2, " \t\n");
	}
	else if (!ft_strncmp(line, "WE", 2))
	{
		if (textures->we)
			return (perror("Duplicate WE"), 1);
		textures->we = ft_strtrim(line + 2, " \t\n");
	}
	else if (!ft_strncmp(line, "EA", 2))
	{
		if (textures->ea)
			return (perror("Duplicate EA"), 1);
		textures->ea = ft_strtrim(line + 2, " \t\n");
	}
	return (0);
}

int	handle_color_line(t_textures *textures, char *line)
{
	if (!ft_strncmp(line, "F ", 1))
	{
		if (textures->floor)
			return (perror("Duplicate F"), 1);
		textures->floor = ft_strtrim(line + 1, " \t\n");
	}
	else if (!ft_strncmp(line, "C ", 1))
	{
		if (textures->ceiling)
			return (perror("Duplicate C"), 1);
		textures->ceiling = ft_strtrim(line + 1, " \t\n");
	}
	if (parse_rgb(textures->floor, &textures->floor_rgb))
		return (1);
	if (parse_rgb(textures->ceiling, &textures->ceiling_rgb))
		return (1);
	else
		return (0);
	return (0);
}

int	parse_line(t_textures *textures, char *line)
{
	char	*trimmed_line;
	int		ret;

	trimmed_line = ft_strtrim(line, " \t\n");
	ret = 0;
	if (!trimmed_line || trimmed_line[0] == '\0')
		return (free(trimmed_line), 0);
	ret = handle_texture_line(textures, trimmed_line);
	if (ret != 0)
		return (free(trimmed_line), ret);
	ret = handle_color_line(textures, trimmed_line);
	if (ret != 0)
		return (free(trimmed_line), ret);
	return (free(trimmed_line), 0);
}

int	check_textures(t_textures *textures)
{
	if (!textures->no || !textures->so || !textures->we || !textures->ea
		|| !textures->floor || !textures->ceiling)
	{
		perror("Missing texture paths");
		return (1);
	}
	return (0);
}

int	parse_textures_colors(t_textures *textures, char *file_path)
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
		if (parse_line(textures, line))
		{
			free(line);
			close(fd);
			return (destroy_textures(textures), 1);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (check_textures(textures))
		return (destroy_textures(textures), close(fd), 1);
	return (close(fd), 0);
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
	free(textures);
	return (0);
}

int	convert_rgb(unsigned int r, unsigned int g, unsigned int b)
{
	if (r > 255 || g > 255 || b > 255)
		return (perror("RGB values must be between 0 and 255"), -1);
	return ((r << 16) | (g << 8) | b);
}

int	parse_rgb(const char *str, int *res)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	int		i;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (perror("Invalid RGB format"), 1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (perror("RGB values must be between 0 and 255"), 1);
	*res = convert_rgb(r, g, b);
	i = 0;
	while (rgb[i])
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
	return (0);
}
