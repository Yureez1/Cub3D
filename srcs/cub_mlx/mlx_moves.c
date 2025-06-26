/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:09:21 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/26 14:39:55 by leaugust         ###   ########.fr       */
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

int	handle_keypress(int keycode, t_map *map)
{
	t_game	*game;

	game = map->game;
	if (keycode == KEY_ESC)
	{
		destroy_map(map);
		exit(0);
	}
	else if (keycode == KEY_W)
		game->key[MOVE_FWD] = 1;
	else if (keycode == KEY_S)
		game->key[MOVE_BWD] = 1;
	else if (keycode == KEY_A)
		game->key[MOVE_LEFT] = 1;
	else if (keycode == KEY_D)
		game->key[MOVE_RIGHT] = 1;
	else if (keycode == KEY_LEFT)
		game->key[ROTATE_LEFT] = 1;
	else if (keycode == KEY_RIGHT)
		game->key[ROTATE_RIGHT] = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_map *map)
{
	t_game	*game;

	game = map->game;
	if (keycode == KEY_W)
		game->key[MOVE_FWD] = 0;
	else if (keycode == KEY_S)
		game->key[MOVE_BWD] = 0;
	else if (keycode == KEY_A)
		game->key[MOVE_LEFT] = 0;
	else if (keycode == KEY_D)
		game->key[MOVE_RIGHT] = 0;
	else if (keycode == KEY_LEFT)
		game->key[ROTATE_LEFT] = 0;
	else if (keycode == KEY_RIGHT)
		game->key[ROTATE_RIGHT] = 0;
	return (0);
}
