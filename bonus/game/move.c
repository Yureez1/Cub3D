/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:16:43 by leaugust          #+#    #+#             */
/*   Updated: 2025/07/15 16:46:25 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

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

void	apply_move(t_map *map, double v_x, double v_y)
{
	map->player_x += v_x;
	map->player_y += v_y;
	if (is_player_out_of_bounds(map))
	{
		printf("Error: Player left the map! Exiting...\n");
		close_window(map);
	}
}
