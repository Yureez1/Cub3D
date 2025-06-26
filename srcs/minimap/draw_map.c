/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:28:54 by leaugust          #+#    #+#             */
/*   Updated: 2025/06/26 17:25:21 by jbanchon         ###   ########.fr       */
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
			// draw_square(rect, map->game);
			x++;
		}
		y++;
	}
}

void	set_direction(t_map *map)
{
	int		i;
	double	camera_x;
	double	ray_x;
	double	ray_y;

	i = 0;
	while (i < WIDTH)
	{
		camera_x = 2 * i / (double)WIDTH - 1.0;
		ray_x = map->dir_x + map->plane_x * camera_x;
		ray_y = map->dir_y + map->plane_y * camera_x;
		draw_line(map, map->game, ray_x, ray_y, i);
		i++;
	}
}

void	draw_line(t_map *map, t_game *game, double ray_x, double ray_y, int i)
{
	int		mapX;
	int		mapY;
	double	rayDirX;
	double	rayDirY;
	double	deltaDistX;
	double	deltaDistY;
	int		hit;
	int		side;
	double	perpWallDist;
	double	height;
	int		startY;
	int		endY;
	int		color;
	double	angle;

	angle = atan2(ray_y, ray_x);
	mapX = (int)map->player_x;
	mapY = (int)map->player_y;
	rayDirX = cos(angle);
	rayDirY = sin(angle);
	deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
	deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
	int stepX, stepY;
	double sideDistX, sideDistY;
	if (rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (map->player_x - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - map->player_x) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (map->player_y - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - map->player_y) * deltaDistY;
	}
	hit = 0;
	side = 0;
	while (!hit)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		if (map->map[mapY][mapX] == '1')
			hit = 1;
	}
	if (side == 0)
		perpWallDist = (mapX - map->player_x + (1 - stepX) / 2) / rayDirX;
	else
		perpWallDist = (mapY - map->player_y + (1 - stepY) / 2) / rayDirY;
	height = (HEIGHT * TILE_SIZE) / perpWallDist;
	if (height > HEIGHT)
		height = HEIGHT;
	startY = (HEIGHT - height) / 2;
	endY = startY + height;
	if (startY < 0)
		startY = 0;
	if (endY > HEIGHT)
		endY = HEIGHT;
	color = (side == 1) ? 0xAAAAAA : 0xFFFFFF;
	for (int y = startY; y < endY; y++)
		put_pixel(i, y, color, game);
}
