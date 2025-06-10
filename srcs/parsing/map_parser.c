/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:50:26 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/10 15:52:11 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	init_struct(t_map *map)
{
	map->map = NULL;
	map->x = 0;
	map->y = 0;
	map->width = 0;
	map->height = 0;
	map->player_x = -1;
	map->player_y = -1;
	return (0);
}

int	parse_map(t_map *map, char *file_path)
{
	int	fd;

	printf("=== Starting map parsing ===\n");
	fd = open_map_file(file_path);
	if (fd < 0)
	{
		printf("Error: Failed to open file %s\n", file_path);
		return (1);
	}
	printf("Successfully opened %s (fd=%d)\n", file_path, fd);
	if (read_map_lines(fd, map))
	{
		printf("Error reading map lines\n");
		close(fd);
		return (1);
	}
	close(fd);
	printf("Map reading complete - Dimensions: %dx%d\n", map->width,
		map->height);
	if (validate_map(map))
	{
		printf("Error: Map validation failed\n");
		return (1);
	}
	printf("Map validated successfully\n");
	if (find_player_position(map))
	{
		printf("Error: Player position not found\n");
		return (1);
	}
	printf("Player found at (%d, %d) facing %c\n", map->player_x, map->player_y,
		map->player_dir);
	printf("=== Map parsing completed successfully ===\n");
	return (0);
}
