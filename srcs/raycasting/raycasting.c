/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:29:22 by leaugust          #+#    #+#             */
/*   Updated: 2025/07/01 13:40:25 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	calc_camera_ray(double *ray_x, double *ray_y, t_map *map, int i)
{
	double	camera_x;

	camera_x = 2 * i / (double)WIDTH - 1;
	*ray_x = map->dir_x + map->plane_x * camera_x;
	*ray_y = map->dir_y + map->plane_y * camera_x;
}

void	set_ray_data(t_map *map, t_ray *ray, double ray_x, double ray_y)
{
	ray->map_x = (int)map->player_x;
	ray->map_y = (int)map->player_y;
	ray->dir_x = ray_x;
	ray->dir_y = ray_y;
	if (ray_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray_x);
	if (ray_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray_y);
}

void	init_dda(t_map *map, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (map->player_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - map->player_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (map->player_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - map->player_y)
			* ray->delta_dist_y;
	}
}

int	perform_dda(t_map *map, t_ray *ray)
{
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_y < 0 || ray->map_x >= map->width
			|| ray->map_y >= map->height)
			return (0);
		if (map->map[ray->map_y][ray->map_x] == '1')
			return (1);
	}
	return (0);
}

void	calc_perp_dist(t_map *map, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->side != 0)
			ray->perp_dist = (ray->map_x - map->player_x + (1.0
						- (double)ray->step_x) / 2.0) / ray->dir_x;
		else
			ray->perp_dist = 1e30;
	}
	else
	{
		if (ray->dir_y != 0)
			ray->perp_dist = (ray->map_y - map->player_y + (1.0
						- (double)ray->step_y) / 2.0) / ray->dir_y;
		else
			ray->perp_dist = 1e30;
	}
}
