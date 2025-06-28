/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_projection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 13:37:43 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/28 13:37:49 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	calc_projection(t_map *map, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_dist = (ray->map_x - map->player_x + (1.0
					- (double)ray->step_x) / 2.0) / ray->dir_x;
	else
		ray->perp_dist = (ray->map_y - map->player_y + (1.0
					- (double)ray->step_y) / 2.0) / ray->dir_y;
	ray->line_h = (int)(HEIGHT / ray->perp_dist);
	ray->draw_s = -ray->line_h / 2 + HEIGHT / 2;
	if (ray->draw_s < 0)
		ray->draw_s = 0;
	ray->draw_end = ray->line_h / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

int	compute_texx(t_map *map, t_ray *ray)
{
	int			texnum;
	t_textures	*tex;
	double		wall_x;
	int			texx;

	texnum = select_texture(ray);
	tex = &map->game->textures[texnum];
	if (ray->side == 0)
		wall_x = map->player_y + ray->perp_dist * ray->dir_y;
	else
		wall_x = map->player_x + ray->perp_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	texx = (int)(wall_x * tex->width);
	if ((ray->side == 0 && ray->dir_x > 0.0) || (ray->side == 1
			&& ray->dir_y < 0.0))
		texx = tex->width - texx - 1;
	return (texx);
}
