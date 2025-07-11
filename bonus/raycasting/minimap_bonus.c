/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:00:00 by jbanchon          #+#    #+#             */
/*   Updated: 2025/07/11 17:36:59 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

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
	rect.color = 0xCC5500;
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
				rect.color = 0x000F1625;
			else
				rect.color = 0x002D3C23;
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

	offset_x = MINIMAP_PADDING;
	offset_y = MINIMAP_PADDING;
	draw_minimap_cells(map, offset_x, offset_y);
	draw_minimap_player(map, offset_x, offset_y);
}
