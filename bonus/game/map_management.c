/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:19:34 by leaugust          #+#    #+#             */
/*   Updated: 2025/07/11 17:31:25 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	free_map_grid(t_map *map)
{
	int	y;

	if (!map || !map->map)
		return ;
	y = 0;
	while (y < map->height)
	{
		if (map->map[y])
			free(map->map[y]);
		y++;
	}
	free(map->map);
	map->map = NULL;
}

void	destroy_map(t_map *map)
{
	if (!map)
		return ;
	free_map_grid(map);
	if (map->game)
	{
		destroy_mlx(map->game);
		free(map->game);
		map->game = NULL;
	}
	if (map->texpath)
	{
		destroy_texpath(map->texpath);
		free(map->texpath);
		map->texpath = NULL;
	}
	free(map);
}
