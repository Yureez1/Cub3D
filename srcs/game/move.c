/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:16:43 by leaugust          #+#    #+#             */
/*   Updated: 2025/07/15 15:48:57 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	accumulate_vector(t_map *map, double *v_x, double *v_y)
{
	t_game	*game;

	game = map->game;
	*v_x = 0;
	*v_y = 0;
	if (game->key[MOVE_FWD])
	{
		*v_x += map->dir_x * MOVE_SPEED;
		*v_y += map->dir_y * MOVE_SPEED;
	}
	if (game->key[MOVE_BWD])
	{
		*v_x -= map->dir_x * MOVE_SPEED;
		*v_y -= map->dir_y * MOVE_SPEED;
	}
	if (game->key[MOVE_LEFT])
	{
		*v_x -= map->plane_x * MOVE_SPEED;
		*v_y -= map->plane_y * MOVE_SPEED;
	}
	if (game->key[MOVE_RIGHT])
	{
		*v_x += map->plane_x * MOVE_SPEED;
		*v_y += map->plane_y * MOVE_SPEED;
	}
}

static void	normalize_vector(double *v_x, double *v_y)
{
	double	mag;

	mag = sqrt((*v_x) * (*v_x) + (*v_y) * (*v_y));
	if (mag > 0.0)
	{
		*v_x = (*v_x / mag) * MOVE_SPEED;
		*v_y = (*v_y / mag) * MOVE_SPEED;
	}
}

static int	is_player_out_of_bounds(t_map *map)
{
	int	player_x;
	int	player_y;

	player_x = (int)map->player_x;
	player_y = (int)map->player_y;
	if (player_x < 0 || player_x >= map->width || player_y < 0
		|| player_y >= map->height)
		return (1);
	return (0);
}

void	calc_move_vector(t_map *map, double *v_x, double *v_y)
{
	accumulate_vector(map, v_x, v_y);
	normalize_vector(v_x, v_y);
}

void	apply_move(t_map *map, double v_x, double v_y)
{
	map->player_x += v_x;
	map->player_y += v_y;
	if (is_player_out_of_bounds(map))
	{
		printf("Player left the map! Exiting...\n");
		close_window(map);
	}
}
