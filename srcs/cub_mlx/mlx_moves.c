/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:09:21 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/21 12:11:41 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_walkable(t_map *map, double x, double y)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)x;
	grid_y = (int)y;
	if (grid_x < 0 || grid_x >= map->width || grid_y < 0
		|| grid_y >= map->height)
		return (0);
	return (map->map[grid_y][grid_x] != '1');
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
