/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:15:55 by jbanchon          #+#    #+#             */
/*   Updated: 2025/07/15 15:33:35 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_texture_paths(char **paths, t_texpath *texpath)
{
	paths[TEX_NO] = texpath->no;
	paths[TEX_SO] = texpath->so;
	paths[TEX_WE] = texpath->we;
	paths[TEX_EA] = texpath->ea;
}

static int	load_single_texture(t_game *game, t_textures *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width,
			&tex->height);
	if (!tex->img)
		return (1);
	tex->data = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_size,
			&tex->endian);
	return (0);
}

static void	cleanup_loaded_textures(t_game *game, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (game->textures[i].img)
		{
			mlx_destroy_image(game->mlx, game->textures[i].img);
			game->textures[i].img = NULL;
		}
		i++;
	}
}

int	load_textures(t_map *map)
{
	char		*paths[NB_TEXTURES];
	int			i;
	t_textures	*tex;

	init_texture_paths(paths, map->texpath);
	i = 0;
	while (i < NB_TEXTURES)
	{
		tex = &map->game->textures[i];
		if (load_single_texture(map->game, tex, paths[i]))
		{
			cleanup_loaded_textures(map->game, i);
			return (1);
		}
		i++;
	}
	return (0);
}
