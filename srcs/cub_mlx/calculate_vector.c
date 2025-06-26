/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:04:48 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/26 12:00:48 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	accumulate_vector(t_map *map, double *v_x, double *v_y)
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

void	normalize_vector(double *v_x, double *v_y)
{
	double	mag;

	mag = sqrt((*v_x) * (*v_x) + (*v_y) * (*v_y));
	if (mag > 0.0)
	{
		*v_x = (*v_x / mag) * MOVE_SPEED;
		*v_y = (*v_y / mag) * MOVE_SPEED;
	}
}

void	calc_move_vector(t_map *map, double *v_x, double *v_y)
{
	accumulate_vector(map, v_x, v_y);
	normalize_vector(v_x, v_y);
}

void	rotate_left(t_map *map)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = map->dir_x;
	old_plane_x = map->plane_x;
	map->dir_x = map->dir_x * cos(-ROTATE_SPEED) - map->dir_y
		* sin(-ROTATE_SPEED);
	map->dir_y = old_dir_x * sin(-ROTATE_SPEED) + map->dir_y
		* cos(-ROTATE_SPEED);
	map->plane_x = map->plane_x * cos(-ROTATE_SPEED) - map->plane_y
		* sin(-ROTATE_SPEED);
	map->plane_y = old_plane_x * sin(-ROTATE_SPEED) + map->plane_y
		* cos(-ROTATE_SPEED);
	map->player_angle = atan2(map->dir_y, map->dir_x);
	printf("Rotated right to (%.2f, %.2f)\n", map->player_x, map->player_y);
}

void	rotate_right(t_map *map)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = map->dir_x;
	old_plane_x = map->plane_x;
	map->dir_x = map->dir_x * cos(ROTATE_SPEED) - map->dir_y
		* sin(ROTATE_SPEED);
	map->dir_y = old_dir_x * sin(ROTATE_SPEED) + map->dir_y * cos(ROTATE_SPEED);
	map->plane_x = map->plane_x * cos(ROTATE_SPEED) - map->plane_y
		* sin(ROTATE_SPEED);
	map->plane_y = old_plane_x * sin(ROTATE_SPEED) + map->plane_y
		* cos(ROTATE_SPEED);
	map->player_angle = atan2(map->dir_y, map->dir_x);
	printf("Rotated left to (%.2f, %.2f)\n", map->player_x, map->player_y);
}
