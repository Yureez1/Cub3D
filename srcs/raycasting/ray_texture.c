/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 13:37:55 by jbanchon          #+#    #+#             */
/*   Updated: 2025/07/15 15:38:27 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	select_texture(t_ray *ray)
{
	int	texnum;

	if (ray->side == 0)
	{
		if (ray->dir_x > 0.0)
			texnum = TEX_NO;
		else
			texnum = TEX_SO;
	}
	else
	{
		if (ray->dir_y > 0.0)
			texnum = TEX_WE;
		else
			texnum = TEX_EA;
	}
	return (texnum);
}

static void	draw_textures(t_map *map, t_ray *ray, int x, int texx)
{
	t_textures	*tex;

	tex = &map->game->textures[select_texture(ray)];
	ray->step_tex = (double)tex->height / ray->line_h;
	ray->tex_pos = (ray->draw_s - HEIGHT / 2.0 + ray->line_h / 2.0)
		* ray->step_tex;
	ray->y = ray->draw_s;
	while (ray->y <= ray->draw_end)
	{
		ray->ty = (int)ray->tex_pos;
		ray->tex_pos += ray->step_tex;
		if (ray->ty < 0)
			ray->ty = 0;
		if (ray->ty >= tex->height)
			ray->ty = tex->height - 1;
		ray->row = (char *)tex->data + ray->ty * tex->line_size;
		ray->color = ((int *)ray->row)[texx];
		put_pixel(x, ray->y, ray->color, map->game);
		ray->y++;
	}
}

void	draw_column(t_map *map, t_ray *ray, int x)
{
	int	texx;

	texx = compute_texx(map, ray);
	if (texx < 0)
		texx = 0;
	if (texx >= map->game->textures[select_texture(ray)].width)
		texx = map->game->textures[select_texture(ray)].width - 1;
	draw_textures(map, ray, x, texx);
}
