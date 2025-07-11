/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:17:42 by leaugust          #+#    #+#             */
/*   Updated: 2025/07/11 17:31:23 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

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
