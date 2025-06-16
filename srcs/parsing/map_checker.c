/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:49:24 by leaugust          #+#    #+#             */
/*   Updated: 2025/06/14 21:29:42 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_out_of_bounds(int x, int y, int width, int height)
{
	return (x < 0 || y < 0 || x >= width || y >= height);
}

int	is_touching_void(t_map *map, int x, int y)
{
	int	i;
	int	nx;
	int	ny;

	i = 0;
	while (i < 4)
	{
		if (i == 0)
			nx = x - 1;
		else if (i == 1)
			nx = x + 1;
		else
			nx = x;
		if (i == 2)
			ny = y - 1;
		else if (i == 3)
			ny = y + 1;
		else
			ny = y;
		if (!is_out_of_bounds(nx, ny, map->width, map->height)
			&& map->map[ny][nx] == ' ')
			return (1);
		i++;
	}
	return (0);
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
