/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_enclosure.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:49:24 by leaugust          #+#    #+#             */
/*   Updated: 2025/06/10 15:46:29 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_out_of_bounds(int x, int y, int width, int height)
{
	return (x < 0 || y < 0 || x >= width || y >= height);
}

int	is_touching_void(char **map, int x, int y, int width, int height)
{
	int		dx[] = {-1, 1, 0, 0};
	int		dy[] = {0, 0, -1, 1};
	int		i;
	int		nx;
	int		ny;
	char	neighbor;

	i = 0;
	while (i < 4)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		if (!is_out_of_bounds(nx, ny, width, height))
		{
			neighbor = map[ny][nx];
			if (neighbor == ' ')
				return (1);
		}
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
				if (is_touching_void(map->map, x, y, map->width, map->height))
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

static void	print_map(t_map *map)
{
	int	y;

	y = 0;
	printf("=== MAP ===\n");
	while (y < map->height)
	{
		printf("%s\n", map->map[y]);
		y++;
	}
	printf("===========\n");
}

int	validate_map(t_map *map)
{
	printf("Map before filling:\n");
	print_map(map);
	if (validate_void_surroundings(map))
	{
		printf("Error: map not closed (0 or player touches space)\n");
		return (1);
	}
	printf("Void surroundings validated.\n");
	fill_voids_with_walls(map);
	printf("Map after filling:\n");
	print_map(map);
	return (0);
}
