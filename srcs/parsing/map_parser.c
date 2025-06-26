/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:50:26 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/26 17:24:29 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	parse_map(t_map *map, char *file_path)
{
	int	fd;

	printf("=== Starting map parsing ===\n");
	fd = open_map_file(file_path);
	if (fd < 0)
		return (printf("Error: Failed to open file %s\n", file_path), 1);
	printf("Successfully opened %s (fd=%d)\n", file_path, fd);
	if (parse_textures_colors(map->textures, file_path))
		return ((close(fd), printf("Error parsing textures and colors\n")), 1);
	close(fd);
	fd = open_map_file(file_path);
	if (read_map_lines(fd, map))
		return ((close(fd), printf("Error reading map lines\n")), 1);
	close(fd);
	printf("Map reading complete - Dimensions: %dx%d\n", map->width,
		map->height);
	if (validate_map(map))
		return (printf("Error: Map validation failed\n"), 1);
	printf("Player found at (%f, %f) facing %c\n", map->player_x, map->player_y,
		map->player_dir);
	printf("=== Map parsing completed successfully ===\n");
	return (0);
}
