/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:47:21 by leaugust          #+#    #+#             */
/*   Updated: 2025/06/10 14:58:02 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
