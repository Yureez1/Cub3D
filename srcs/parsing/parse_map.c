/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:50:26 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/06 14:52:12 by jbanchon         ###   ########.fr       */
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

static int	check_top_bot(t_map *map)
{
	char	c;

	map->y = 0;
	map->x = 0;
	while (map->y < map->height)
	{
		while (map->x < map->width)
		{
			c = map->map[map->y][map->x];
			if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
				|| c == 'W')
			{
				if (map->y == 0 || map->y == map->height - 1)
				{
					if (c != '1')
						return (1);
				}
				if (map[map->y + 1][map->x] == ' ' || map[map->y
					- 1][map->x] == ' ')
					return (1);
			}
			map->x++;
		}
		map->y++;
	}
	return (0);
}

static int	check_left_right(t_map *map)
{
	char	c;

	map->y = 0;
	map->x = 0;
	while (map->y < map->height)
	{
		while (map->x < map->width)
		{
			c = map->map[map->y][map->x];
			if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
				|| c == 'W')
			{
				if (map->y == 0 || map->y == map->height - 1)
				{
					if (c != '1')
						return (1);
				}
				if (map[map->y][map->x + 1] == ' ' || map[map->y][map->x
					- 1] == ' ')
					return (1);
			}
			map->x++;
		}
		map->y++;
	}
	return (0);
}

int	parse_map(t_map *map, char *file_path)
{
	int		fd;
	char	*line;

	// init_struct(map);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file"), 1);
	while (get_next_line(fd) > 0)
	{
		if (check_left_right(map) || check_top_bot(map))
		{
			free(line);
			close(fd);
			return (perror("Map is not closed"), 1);
		}
		printf("Line: %s\n", line);
	}
}
