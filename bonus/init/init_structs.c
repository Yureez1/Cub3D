/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:28:49 by jbanchon          #+#    #+#             */
/*   Updated: 2025/07/11 17:30:06 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	init_textures(t_textures *textures)
{
	int	i;

	i = 0;
	while (i < NB_TEXTURES)
	{
		textures[i].img = NULL;
		textures[i].data = NULL;
		textures[i].width = 0;
		textures[i].height = 0;
		textures[i].bpp = 0;
		textures[i].line_size = 0;
		textures[i].endian = 0;
		i++;
	}
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
	map->dir_x = 0.0;
	map->dir_y = 0.0;
	map->plane_x = 0.0;
	map->plane_y = 0.0;
	map->player_angle = 0.0;
	map->player_dir = 0;
	map->game = malloc(sizeof(t_game));
	if (!map->game)
		return (perror("Failed to allocate memory for game struct"), 1);
	init_game_struct(map->game);
	init_textures(map->game->textures);
	map->texpath = malloc(sizeof(t_texpath));
	if (!map->texpath)
		return (perror("Failed to allocate memory for texpath"), 1);
	init_texpath(map->texpath);
	return (0);
}

int	init_texpath(t_texpath *texpath)
{
	texpath->no = NULL;
	texpath->so = NULL;
	texpath->we = NULL;
	texpath->ea = NULL;
	texpath->floor = NULL;
	texpath->ceiling = NULL;
	texpath->floor_rgb = 0;
	texpath->ceiling_rgb = 0;
	return (0);
	texpath->ceiling = NULL;
	texpath->floor_rgb = -1;
	texpath->ceiling_rgb = -1;
	return (0);
}
