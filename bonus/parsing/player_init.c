/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:47:21 by leaugust          #+#    #+#             */
/*   Updated: 2025/07/11 17:30:20 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	set_player_position(t_map *map, int x, int y)
{
	char	c;

	c = map->map[y][x];
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (0);
	map->player_x = x + 0.5;
	map->player_y = y + 0.5;
	map->player_dir = c;
	if (c == 'N')
		map->player_angle = 3 * M_PI / 2;
	else if (c == 'S')
		map->player_angle = M_PI / 2;
	else if (c == 'E')
		map->player_angle = 0;
	else if (c == 'W')
		map->player_angle = M_PI;
	map->map[y][x] = '0';
	return (1);
}

void	fill_voids_with_walls(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == ' ')
				map->map[y][x] = '1';
			x++;
		}
		y++;
	}
}
