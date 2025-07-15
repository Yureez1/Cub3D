/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:20:25 by leaugust          #+#    #+#             */
/*   Updated: 2025/07/15 15:03:45 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

static void	rotate_left(t_map *map)
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
}

static void	rotate_right(t_map *map)
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
