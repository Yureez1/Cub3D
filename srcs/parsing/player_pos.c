/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:47:21 by leaugust          #+#    #+#             */
/*   Updated: 2025/06/17 10:54:09 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int check_single_player(t_map *map)
{
	int count;
	int y;
	int x;

	count = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width && map->map[y][x])
		{
			if (map->map[y][x] == 'N' || map->map[y][x] == 'S' || map->map[y][x] == 'E' || map->map[y][x] == 'W')
				count++;
			x++;
		}
		y++;
	}
	if (count == 0)
		return (perror("No player position found in map"), 1);
	if (count > 1)
		return (perror("Multiple player positions found in map"), 1);
	return (0);
}

int	set_player_position(t_map *map, int x, int y)
{
	char	c;

	c = map->map[y][x];
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (0);
	map->player_x = x;
	map->player_y = y;
	map->player_dir = c;
	if (c == 'N')
		map->player_angle = 3 * M_PI / 2;
	else if (c == 'S')
		map->player_angle = M_PI / 2;
	else if (c == 'E')
		map->player_angle = 0;
	else if (c == 'W')
		map->player_angle = M_PI;
	printf("Player at (%d, %d), facing '%c', angle %.2f rad\n", x, y, c,
		map->player_angle);
	return (1);
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
