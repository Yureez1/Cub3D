/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:15:55 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/27 16:02:49 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	load_textures(t_map *map)
{
	char		*paths[NB_TEXTURES] = {map->texpath->no, map->texpath->so,
				map->texpath->we, map->texpath->ea};
	int			i;
	t_textures	*tex;

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
