/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:00:00 by jbanchon          #+#    #+#             */
/*   Updated: 2025/07/11 17:36:54 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	apply_move(t_map *map, double v_x, double v_y)
{
	if (is_walkable(map, map->player_x + v_x, map->player_y))
		map->player_x += v_x;
	if (is_walkable(map, map->player_x, map->player_y + v_y))
		map->player_y += v_y;
}
