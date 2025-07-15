/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:00:00 by jbanchon          #+#    #+#             */
/*   Updated: 2025/07/15 15:00:43 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

static void	get_bounding_cells(double px, double py, t_bounds *bounds)
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

static int	is_cell_walkable(t_map *map, int x, int y)
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
