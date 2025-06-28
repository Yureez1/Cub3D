/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 13:36:29 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/28 13:37:19 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	compute_camera_ray(t_map *map, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIDTH - 1.0;
	ray->dir_x = map->dir_x + map->plane_x * camera_x;
	ray->dir_y = map->dir_y + map->plane_y * camera_x;
	ray->map_x = (int)map->player_x;
	ray->map_y = (int)map->player_y;
}

void	compute_delta_distances(t_ray *ray)
{
	if (ray->dir_x == 0.0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0.0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
}

void	compute_step_and_side(t_map *map, t_ray *ray)
{
	if (ray->dir_x < 0.0)
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
	if (ray->dir_y < 0.0)
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

void	init_ray(t_map *map, t_ray *ray, int x)
{
	compute_camera_ray(map, ray, x);
	compute_delta_distances(ray);
	compute_step_and_side(map, ray);
}
