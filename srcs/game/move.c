/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:16:43 by leaugust          #+#    #+#             */
/*   Updated: 2025/07/05 16:05:38 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_bounding_cells(double px, double py, t_bounds *bounds)
{
	(void)px;
	(void)py;
	(void)bounds;
}

int	is_cell_walkable(t_map *map, int x, int y)
{
	(void)map;
	(void)x;
	(void)y;
	return (1);
}

int	is_walkable(t_map *map, double px, double py)
{
	(void)map;
	(void)px;
	(void)py;
	return (1);
}

int	is_player_out_of_bounds(t_map *map)
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
