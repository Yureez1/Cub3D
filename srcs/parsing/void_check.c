/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   void_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:04:04 by leaugust          #+#    #+#             */
/*   Updated: 2025/07/04 14:15:43 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_out_of_bounds(int x, int y, int width, int height)
{
	return (x < 0 || y < 0 || x >= width || y >= height);
}

int	check_void_at(t_map *map, int x, int y)
{
	int	len;

	if (is_out_of_bounds(x, y, map->width, map->height))
		return (1);
	len = ft_strlen(map->map[y]);
	if (x >= len)
		return (1);
	if (map->map[y][x] == ' ')
		return (1);
	return (0);
}

int	is_touching_void(t_map *map, int x, int y)
{
	if (check_void_at(map, x - 1, y))
		return (1);
	if (check_void_at(map, x + 1, y))
		return (1);
	if (check_void_at(map, x, y - 1))
		return (1);
	if (check_void_at(map, x, y + 1))
		return (1);
	return (0);
}
