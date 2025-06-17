/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:01:02 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/17 16:32:19 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	init_mlx(t_map *map)
{
	if (!map)
		return (perror("Map structure is NULL"), 1);
	map->mlx = mlx_init();
	if (!map->mlx)
		return (perror("Failed to initialize mlx"), 1);
	map->mlx_win = mlx_new_window(map->mlx, 800, 600, "Cub3D Window");
	if (!map->mlx_win)
	{
		mlx_destroy_display(map->mlx);
		free(map->mlx);
		return (perror("Failed to create window"), 1);
	}
	return (0);
}

void	destroy_mlx(t_map *map)
{
	if (!map || !map->mlx)
		return ;
	if (map->mlx_win)
	{
		mlx_destroy_window(map->mlx, map->mlx_win);
		map->mlx_win = NULL;
	}
	mlx_destroy_display(map->mlx);
	free(map->mlx);
	map->mlx = NULL;
	map->mlx_win = NULL;
}

void	destroy_map(t_map *map)
{
	int	y;

	if (!map || !map->map)
		return ;
	if (map->map)
	{
		y = 0;
		while (y < map->height)
		{
			free(map->map[y]);
			y++;
		}
	}
	free(map->map);
	map->map = NULL;
	if (map->mlx)
		destroy_mlx(map);
}
