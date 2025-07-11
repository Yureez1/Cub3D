/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:29:05 by leaugust          #+#    #+#             */
/*   Updated: 2025/07/11 17:38:08 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

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

void	draw_wall_column(t_game *game, int i, t_ray *ray)
{
	int		y;
	int		start;
	int		end;
	double	height;
	int		color;

	height = HEIGHT / ray->perp_dist;
	if (height > HEIGHT)
		height = HEIGHT;
	start = (HEIGHT - height) / 2;
	end = start + height;
	if (ray->side == 1)
		color = 0xAAAAAA;
	else
		color = 0xFFFFFF;
	if (start < 0)
		start = 0;
	if (end > HEIGHT)
		end = HEIGHT;
	y = start;
	while (y < end)
	{
		put_pixel(i, y, color, game);
		y++;
	}
}

void	draw_line(t_map *map, double ray_x, double ray_y, int i)
{
	t_ray	ray;

	set_ray_data(map, &ray, ray_x, ray_y);
	init_dda(map, &ray);
	if (!perform_dda(map, &ray))
		return ;
	calc_perp_dist(map, &ray);
	draw_wall_column(map->game, i, &ray);
}
