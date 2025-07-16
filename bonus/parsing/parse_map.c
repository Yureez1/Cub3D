/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:17:17 by leaugust          #+#    #+#             */
/*   Updated: 2025/07/16 15:27:59 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

static int	open_map_file(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error : Cannot open file");
		return (-1);
	}
	return (fd);
}

static char	**allocate_temp_map(void)
{
	char	**temp_map;
	int		i;

	temp_map = malloc(sizeof(char *) * 1024);
	if (!temp_map)
	{
		printf("Malloc failed for temp_map");
		return (NULL);
	}
	i = 0;
	while (i < 1024)
		temp_map[i++] = NULL;
	return (temp_map);
}

static int	fill_temp_map(int fd, char **temp_map, int *height, int *max_width)
{
	char	*line;
	int		started;

	started = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!started && handle_pre_map_line(line, &started))
		{
			line = get_next_line(fd);
			continue ;
		}
		else if (started && handle_map_line(line, temp_map, height, max_width))
			return (1);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}

static int	read_map_lines(int fd, t_map *map)
{
	char	**temp_map;
	int		max_width;
	int		height;

	max_width = 0;
	height = 0;
	temp_map = allocate_temp_map();
	if (!temp_map)
		return (1);
	if (fill_temp_map(fd, temp_map, &height, &max_width))
	{
		free_temp_map(temp_map);
		return (1);
	}
	map->height = height;
	map->width = max_width;
	if (finalize_map(map, temp_map))
	{
		free_temp_map(temp_map);
		return (1);
	}
	return (0);
}

int	parse_map(t_map *map, char *file_path)
{
	int	fd;

	fd = open_map_file(file_path);
	if (fd < 0)
		return (printf("Error: Failed to open file %s\n", file_path), 1);
	if (parse_textures_colors(map->texpath, file_path))
		return ((close(fd), printf("Error: Invalid file settings\n")), 1);
	map->floor_color = map->texpath->floor_rgb;
	map->ceiling_color = map->texpath->ceiling_rgb;
	close(fd);
	fd = open_map_file(file_path);
	if (read_map_lines(fd, map))
		return ((close(fd), printf("Error: Invalid map lines\n")), 1);
	close(fd);
	if (validate_map(map))
		return (1);
	return (0);
}
