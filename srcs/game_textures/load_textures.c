/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:15:55 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/28 13:42:18 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	load_textures(t_map *map)
{
	char		*paths[NB_TEXTURES];
	int			i;
	t_textures	*tex;

	paths[TEX_NO] = map->texpath->no;
	paths[TEX_SO] = map->texpath->so;
	paths[TEX_WE] = map->texpath->we;
	paths[TEX_EA] = map->texpath->ea;
	i = 0;
	while (i < NB_TEXTURES)
	{
		tex = &map->game->textures[i];
		tex->img = mlx_xpm_file_to_image(map->game->mlx, paths[i], &tex->width,
				&tex->height);
		if (!tex->img)
		{
			perror("Failed to load texture");
			return (1);
		}
		tex->data = (int *)mlx_get_data_addr(tex->img, &tex->bpp,
				&tex->line_size, &tex->endian);
		i++;
	}
	return (0);
}
