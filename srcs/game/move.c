/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:16:43 by leaugust          #+#    #+#             */
/*   Updated: 2025/06/26 20:17:25 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

void	apply_move(t_map *map, double v_x, double v_y)
{
	if (is_walkable(map, map->player_x + v_x, map->player_y))
		map->player_x += v_x;
	if (is_walkable(map, map->player_x, map->player_y + v_y))
		map->player_y += v_y;
}

void	apply_rotation(t_map *map)
{
	t_game	*game;

	game = map->game;
	if (game->key[ROTATE_LEFT])
		rotate_left(map);
	else if (game->key[ROTATE_RIGHT])
		rotate_right(map);
}
