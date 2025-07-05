/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:00:00 by jbanchon          #+#    #+#             */
/*   Updated: 2025/07/05 16:07:23 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../srcs/inc/cub3d.h"

// Version bonus avec collisions complètes
int	touch(t_map *map, double ray_x, double ray_y)
{
	int	x;
	int	y;

	x = (int)(ray_x);
	y = (int)(ray_y);
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (1);
	return (map->map[y][x] == '1');
}

void	get_bounding_cells(double px, double py, t_bounds *bounds)
{
	int	left;
	int	right;
	int	top;
	int	bottom;

	left = (int)(px * TILE_SIZE) - PLAYER_SIZE / 2;
	right = (int)(px * TILE_SIZE) + PLAYER_SIZE / 2;
	top = (int)(py * TILE_SIZE) - PLAYER_SIZE / 2;
	bottom = (int)(py * TILE_SIZE) + PLAYER_SIZE / 2;
	bounds->left_cell = left / TILE_SIZE;
	bounds->right_cell = right / TILE_SIZE;
	bounds->top_cell = top / TILE_SIZE;
	bounds->bottom_cell = bottom / TILE_SIZE;
}

int	is_cell_walkable(t_map *map, int x, int y)
{
	if (y < 0)
		return (0);
	if (y >= map->height)
		return (0);
	if (x < 0)
		return (0);
	if (x >= map->width)
		return (0);
	if (map->map[y][x] == '1')
		return (0);
	return (1);
}

int	is_walkable(t_map *map, double px, double py)
{
	t_bounds	bounds;
	int			x;
	int			y;

	get_bounding_cells(px, py, &bounds);
	y = bounds.top_cell;
	while (y <= bounds.bottom_cell)
	{
		x = bounds.left_cell;
		while (x <= bounds.right_cell)
		{
			if (!is_cell_walkable(map, x, y))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}
