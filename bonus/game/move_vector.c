/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:04:48 by jbanchon          #+#    #+#             */
/*   Updated: 2025/07/11 17:31:30 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

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
