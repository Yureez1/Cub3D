/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:18:35 by leaugust          #+#    #+#             */
/*   Updated: 2025/06/26 20:18:40 by leaugust         ###   ########.fr       */
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
