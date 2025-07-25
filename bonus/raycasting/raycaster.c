/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:27:16 by leaugust          #+#    #+#             */
/*   Updated: 2025/07/15 15:04:42 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

static void	draw_floor_ceiling_column(t_map *map, int x, int start, int end)
{
	int	y;

	y = 0;
	while (y < start)
	{
		put_pixel(x, y, map->ceiling_color, map->game);
		y++;
	}
	y = end + 1;
	while (y < HEIGHT)
	{
		put_pixel(x, y, map->floor_color, map->game);
		y++;
	}
}

void	render_walls(t_map *map)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(map, &ray, x);
		if (!perform_dda(map, &ray))
		{
			x++;
			continue ;
		}
		calc_projection(map, &ray);
		draw_floor_ceiling_column(map, x, ray.draw_s, ray.draw_end);
		draw_column(map, &ray, x);
		x++;
	}
}
