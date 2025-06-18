/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:28:49 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/18 12:20:14 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	init_textures(t_textures *textures)
{
	textures->no = NULL;
	textures->so = NULL;
	textures->we = NULL;
	textures->ea = NULL;
	textures->floor = NULL;
	textures->ceiling = NULL;
	textures->floor_rgb = -1;
	textures->ceiling_rgb = -1;
	return (0);
}

int	init_struct(t_map *map)
{
	map->map = NULL;
	map->x = 0;
	map->y = 0;
	map->width = 0;
	map->height = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = '\0';
	map->player_angle = 0;
	map->dir_x = 0;
	map->dir_y = 0;
	map->plane_x = 0;
	map->plane_y = 0;
	map->mlx = NULL;
	map->mlx_win = NULL;
	map->textures = malloc(sizeof(t_textures));
	if (!map->textures)
		return (perror("Failed to allocate memory for textures"), 1);
	return (0);
}
