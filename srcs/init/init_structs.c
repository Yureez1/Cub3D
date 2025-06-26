/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:28:49 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/26 20:02:09 by leaugust         ###   ########.fr       */
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

int	init_game_struct(t_game *game)
{
	int	i;

	game->mlx = NULL;
	game->mlx_win = NULL;
	game->mlx_img = NULL;
	game->bpp = 0;
	game->size_line = 0;
	game->data = NULL;
	game->endian = 0;
	i = 0;
	while (i < COUNT_ACT)
	{
		game->key[i] = 0;
		i++;
	}
	return (0);
}

int	init_struct(t_map *map)
{
	map->map = NULL;
	map->x = 0;
	map->y = 0;
	map->width = 0;
	map->height = 0;
	map->player_x = 0.5;
	map->player_y = 0.5;
	init_player_dir(map);
	map->game = malloc(sizeof(t_game));
	if (!map->game)
		return (perror("Failed to allocate memory for game struct"), 1);
	map->textures = malloc(sizeof(t_textures));
	if (!map->textures)
		return (perror("Failed to allocate memory for textures"), 1);
	init_game_struct(map->game);
	return (0);
}
