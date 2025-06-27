/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:27:44 by leaugust          #+#    #+#             */
/*   Updated: 2025/06/27 11:48:47 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_player(t_rect rect, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < rect.size)
	{
		j = 0;
		while (j < rect.size)
		{
			put_pixel(rect.x + i, rect.y + j, rect.color, game);
			j++;
		}
		i++;
	}
}

void	draw_minimap_player(t_map *map, int offset_x, int offset_y)
{
	t_rect	rect;

	rect.size = MINIMAP_SCALE / 2;
	rect.color = 0xFF0000;
	rect.x = offset_x + map->player_x * MINIMAP_SCALE - rect.size / 2;
	rect.y = offset_y + map->player_y * MINIMAP_SCALE - rect.size / 2;
	draw_player(rect, map->game);
}

void	draw_minimap_cells(t_map *map, int offset_x, int offset_y)
{
	int		x;
	int		y;
	t_rect	rect;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			rect.x = offset_x + x * MINIMAP_SCALE;
			rect.y = offset_y + y * MINIMAP_SCALE;
			rect.size = MINIMAP_SCALE;
			if (map->map[y][x] == '1')
				rect.color = 0x0000FF;
			else
				rect.color = 0xCCCCCC;
			draw_player(rect, map->game);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_map *map)
{
	int	offset_x;
	int	offset_y;

	// offset_x = WIDTH - map->width * MINIMAP_SCALE - MINIMAP_PADDING;
	// offset_y = HEIGHT - map->height * MINIMAP_SCALE - MINIMAP_PADDING;
	offset_x = MINIMAP_PADDING;
	offset_y = MINIMAP_PADDING;
	draw_minimap_cells(map, offset_x, offset_y);
	draw_minimap_player(map, offset_x, offset_y);
}
