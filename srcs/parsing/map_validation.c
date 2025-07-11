/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 21:28:20 by jbanchon          #+#    #+#             */
/*   Updated: 2025/07/11 19:42:26 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	validate_map(t_map *map)
{
	if (check_invalid_char(map))
		return (printf("Error: Invalid map format\n"), 1);
	if (check_single_player(map))
		return (1);
	if (find_player_position(map))
		return (printf("Error: Failed to find player position\n"), 1);
	if (init_player_dir(map))
		return (printf("Error: Failed to initialize player direction\n"), 1);
	if (validate_void_surroundings(map))
		return (printf("Error: Map not closed (0 or player touches space)\n"),
			1);
	fill_voids_with_walls(map);
	return (0);
}

int	check_invalid_char(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width && map->map[y][x])
		{
			if (parse_char(map->map[y][x]))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	check_single_player(t_map *map)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width && map->map[y][x])
		{
			if (map->map[y][x] == 'N' || map->map[y][x] == 'S'
				|| map->map[y][x] == 'E' || map->map[y][x] == 'W')
				count++;
			x++;
		}
		y++;
	}
	if (count == 0)
		return (printf("Error: No player position found in map\n"), 1);
	if (count > 1)
		return (printf("Error: Multiple player positions found in map\n"), 1);
	return (0);
}

int	find_player_position(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (set_player_position(map, x, y))
				return (0);
			x++;
		}
		y++;
	}
	printf("Error: No player position found in map.\n");
	return (1);
}

int	validate_void_surroundings(t_map *map)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			c = map->map[y][x];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (is_touching_void(map, x, y))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
