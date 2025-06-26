/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:27:16 by leaugust          #+#    #+#             */
/*   Updated: 2025/06/26 20:27:34 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_direction(t_map *map)
{
	int		i;
	double	ray_x;
	double	ray_y;

	i = 0;
	while (i < WIDTH)
	{
		calc_camera_ray(&ray_x, &ray_y, map, i);
		draw_line(map, ray_x, ray_y, i);
		i++;
	}
}
