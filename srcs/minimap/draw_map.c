/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:28:54 by leaugust          #+#    #+#             */
/*   Updated: 2025/06/20 15:33:42 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	i;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	i = y * game->size_line + x * (game->bpp / 8);
	game->data[i] = (color & 0xFF);
	game->data[i + 1] = (color >> 8) & 0xFF;
	game->data[i + 2] = (color >> 16) & 0xFF;
}

void	draw_square(t_rect rect, t_game *game)
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

void	draw_minimap(t_map *map)
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
			rect.x = x * TILE_SIZE;
			rect.y = y * TILE_SIZE;
			rect.size = TILE_SIZE;
			if (map->map[y][x] == '1')
				rect.color = 0x0000FF; // Bleu pour mur
			else
				rect.color = 0xCCCCCC; // Gris clair pour sol
			draw_square(rect, map->game);
			x++;
		}
		y++;
	}
}

void	set_direction(t_map *map)
{
	int		i;
	int		len;
	double	x;
	double	y;
	double	dx;
	double	dy;

	i = 0;
	len = 16;
	x = map->player_x * TILE_SIZE;
	y = map->player_y * TILE_SIZE;
	dx = map->dir_x;
	dy = map->dir_y;
	while (i < len)
	{
		int	px = (int)(x + dx * i);
		int	py = (int)(y + dy * i);
		put_pixel(px, py, 0xFF0000, map->game); // rouge
		i++;
	}
}
