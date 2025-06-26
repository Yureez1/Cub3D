/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   laser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:50:24 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/26 12:06:06 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	touch(t_map *map, double ray_x, double ray_y)
{
	int	x;
	int	y;

	x = (int)(ray_x);
	y = (int)(ray_y);
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (1);
	return (map->map[y][x] == '1');
}
