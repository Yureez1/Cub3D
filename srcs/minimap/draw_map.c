/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:28:54 by leaugust          #+#    #+#             */
/*   Updated: 2025/06/26 14:16:47 by leaugust         ###   ########.fr       */
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
				rect.color = 0x0000FF;
			else
				rect.color = 0xCCCCCC;
			draw_square(rect, map->game);
			x++;
		}
		y++;
	}
}

void	set_direction(t_map *map)
{
	double	ray_x;
	double	ray_y;
	int		player_x;
	int		player_y;
	double	fraction;
	double	start_x;
	int		i;

	ray_x = map->player_x;
	ray_y = map->player_y;
	i = 0;
	fraction = FOV / WIDTH;
	start_x = map->player_angle - (FOV / 2);
	while (i < WIDTH)
	{
		draw_line(map, map->game, start_x, i);
		start_x += fraction;
		i++;
	}
	player_x = (int)(ray_x * TILE_SIZE);
	player_y = (int)(ray_y * TILE_SIZE);
	put_pixel(player_x, player_y, 0x00FF00, map->game);
}

void	draw_line(t_map *map, t_game *game, double start_x, int i)
{
	double	cos_angle;
	double	sin_angle;
	double	ray_x;
	double	ray_y;

	(void)i;
	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = map->player_x;
	ray_y = map->player_y;
	while (!touch(map, ray_x, ray_y))
	{
		put_pixel((int)(ray_x * TILE_SIZE), (int)(ray_y * TILE_SIZE), 0xFF0000,
			game);
		ray_x += cos_angle * RAY_STEP;
		ray_y += sin_angle * RAY_STEP;
	}
}
