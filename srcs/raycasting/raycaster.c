/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:27:16 by leaugust          #+#    #+#             */
/*   Updated: 2025/06/27 16:19:03 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void	set_direction(t_map *map)
// {
// 	int		i;
// 	double	ray_x;
// 	double	ray_y;

// 	i = 0;
// 	while (i < WIDTH)
// 	{
// 		calc_camera_ray(&ray_x, &ray_y, map, i);
// 		draw_line(map, ray_x, ray_y, i);
// 		i++;
// 	}
// }

// void	render_walls(t_map *map)
// {
// 	int			x;
// 	t_ray		ray;
// 	int			lineHeight;
// 	int			drawStart;
// 	int			drawEnd;
// 	char		cell;
// 	int			texNum;
// 	t_textures	*tex;
// 	double		wallX;
// 	int			texX;
// 	double		step;
// 	double		texPos;
// 	int			texY;
// 	int			color;

// 	double ray_x, ray_y;
// 	for (x = 0; x < WIDTH; x++)
// 	{
// 		calc_camera_ray(&ray_x, &ray_y, map, x);
// 		set_ray_data(map, &ray, ray_x, ray_y);
// 		init_dda(map, &ray);
// 		if (!perform_dda(map, &ray))
// 			continue ;
// 		calc_perp_dist(map, &ray);
// 		lineHeight = (int)(HEIGHT / ray.perp_dist);
// 		drawStart = -lineHeight / 2 + HEIGHT / 2;
// 		drawEnd = lineHeight / 2 + HEIGHT / 2;
// 		if (drawStart < 0)
// 			drawStart = 0;
// 		if (drawEnd >= HEIGHT)
// 			drawEnd = HEIGHT - 1;
// 		cell = map->map[ray.map_y][ray.map_x];
// 		if (cell == '1')
// 		{
// 			if (ray.side == 0)
// 				texNum = (ray.dir_x > 0 ? TEX_NO : TEX_SO);
// 			else
// 				texNum = (ray.dir_y > 0 ? TEX_WE : TEX_EA);
// 		}
// 		else
// 			continue ;
// 		tex = &map->game->textures[texNum];
// 		wallX = (ray.side == 0) ? map->player_y + ray.perp_dist
// 			* ray.dir_y : map->player_x + ray.perp_dist * ray.dir_x;
// 		wallX -= floor(wallX);
// 		texX = (int)(wallX * tex->width);
// 		if ((ray.side == 0 && ray.dir_x > 0) || (ray.side == 1
// 				&& ray.dir_y < 0))
// 			texX = tex->width - texX - 1;
// 		step = (double)tex->height / lineHeight;
// 		texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;
// 		for (int y = drawStart; y < drawEnd; y++)
// 		{
// 			texY = (int)texPos & (tex->height - 1);
// 			texPos += step;
// 			color = tex->data[texY * tex->width + texX];
// 			put_pixel(x, y, color, map->game);
// 		}
// 	}
// }

void	render_walls(t_map *map)
{
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
		t_ray ray;
	int			hit;
		double perpDist;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
		int texNum;
	t_textures	*tex;
		double wallX;
	int			texX;
	double		stepTex;
	double		texPos;
	int			ty;
	char		*row;
	int			color;

	for (int x = 0; x < WIDTH; ++x)
	{
		// 1) Calculer le rayon caméra
		cameraX = 2.0 * x / (double)WIDTH - 1.0;
		rayDirX = map->dir_x + map->plane_x * cameraX;
		rayDirY = map->dir_y + map->plane_y * cameraX;
		// 2) Initialisation DDA
		ray.map_x = (int)map->player_x;
		ray.map_y = (int)map->player_y;
		ray.dir_x = rayDirX;
		ray.dir_y = rayDirY;
		if (rayDirX == 0.0)
			ray.delta_dist_x = 1e30;
		else
			ray.delta_dist_x = fabs(1.0 / rayDirX);
		if (rayDirY == 0.0)
			ray.delta_dist_y = 1e30;
		else
			ray.delta_dist_y = fabs(1.0 / rayDirY);
		if (ray.dir_x < 0.0)
		{
			ray.step_x = -1;
			ray.side_dist_x = (map->player_x - ray.map_x) * ray.delta_dist_x;
		}
		else
		{
			ray.step_x = 1;
			ray.side_dist_x = (ray.map_x + 1.0 - map->player_x)
				* ray.delta_dist_x;
		}
		if (ray.dir_y < 0.0)
		{
			ray.step_y = -1;
			ray.side_dist_y = (map->player_y - ray.map_y) * ray.delta_dist_y;
		}
		else
		{
			ray.step_y = 1;
			ray.side_dist_y = (ray.map_y + 1.0 - map->player_y)
				* ray.delta_dist_y;
		}
		// 3) DDA loop
		hit = 0;
		while (hit == 0)
		{
			if (ray.side_dist_x < ray.side_dist_y)
			{
				ray.side_dist_x += ray.delta_dist_x;
				ray.map_x += ray.step_x;
				ray.side = 0;
			}
			else
			{
				ray.side_dist_y += ray.delta_dist_y;
				ray.map_y += ray.step_y;
				ray.side = 1;
			}
			if (ray.map_x < 0 || ray.map_x >= map->width || ray.map_y < 0
				|| ray.map_y >= map->height)
			{
				break ;
			}
			if (map->map[ray.map_y][ray.map_x] == '1')
			{
				hit = 1;
			}
		}
		if (hit == 0)
			continue ; // en dehors ou pas de mur
		// 4) Calculer la distance perpendiculaire
		if (ray.side == 0)
		{
			perpDist = (ray.map_x - map->player_x + (1.0 - (double)ray.step_x)
					/ 2.0) / ray.dir_x;
		}
		else
		{
			perpDist = (ray.map_y - map->player_y + (1.0 - (double)ray.step_y)
					/ 2.0) / ray.dir_y;
		}
		// 5) Hauteur de la colonne
		lineHeight = (int)(HEIGHT / perpDist);
		drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		// 6) Sélectionner la texture
		if (map->map[ray.map_y][ray.map_x] == '1')
		{
			if (ray.side == 0)
			{
				if (ray.dir_x > 0.0)
					texNum = TEX_NO;
				else
					texNum = TEX_SO;
			}
			else
			{
				if (ray.dir_y > 0.0)
					texNum = TEX_WE;
				else
					texNum = TEX_EA;
			}
		}
		else
			continue ;
		tex = &map->game->textures[texNum];
		if (ray.side == 0)
			wallX = map->player_y + perpDist * ray.dir_y;
		else
			wallX = map->player_x + perpDist * ray.dir_x;
		wallX -= floor(wallX);
		texX = (int)(wallX * (double)tex->width);
		if (ray.side == 0 && ray.dir_x > 0.0)
			texX = tex->width - texX - 1;
		if (ray.side == 1 && ray.dir_y < 0.0)
			texX = tex->width - texX - 1;
		stepTex = (double)tex->height / (double)lineHeight;
		texPos = (drawStart - HEIGHT / 2.0 + lineHeight / 2.0) * stepTex;
		for (int y = drawStart; y <= drawEnd; ++y)
		{
			ty = (int)texPos;
			texPos += stepTex;
			if (ty < 0)
				ty = 0;
			if (ty >= tex->height)
				ty = tex->height - 1;
			row = (char *)tex->data + ty * tex->line_size;
			color = ((int *)row)[texX];
			put_pixel(x, y, color, map->game);
		}
	}
}
