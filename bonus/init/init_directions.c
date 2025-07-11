/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_directions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:01:37 by leaugust          #+#    #+#             */
/*   Updated: 2025/07/11 18:05:36 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	init_dir_north(t_map *map)
{
	map->dir_x = 0;
	map->dir_y = -1;
	map->plane_x = 0.66;
	map->plane_y = 0;
}

void	init_dir_south(t_map *map)
{
	map->dir_x = 0;
	map->dir_y = 1;
	map->plane_x = -0.66;
	map->plane_y = 0;
}

void	init_dir_east(t_map *map)
{
	map->dir_x = 1;
	map->dir_y = 0;
	map->plane_x = 0;
	map->plane_y = 0.66;
}

void	init_dir_west(t_map *map)
{
	map->dir_x = -1;
	map->dir_y = 0;
	map->plane_x = 0;
	map->plane_y = -0.66;
}

int	init_player_dir(t_map *map)
{
	char	dir;

	dir = map->player_dir;
	if (dir == 'N')
		init_dir_north(map);
	else if (dir == 'S')
		init_dir_south(map);
	else if (dir == 'E')
		init_dir_east(map);
	else if (dir == 'W')
		init_dir_west(map);
	else
	{
		printf("Invalid player direction");
		return (1);
	}
	return (0);
}
