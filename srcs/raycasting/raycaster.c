/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:27:16 by leaugust          #+#    #+#             */
/*   Updated: 2025/06/28 13:38:09 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
		draw_column(map, &ray, x);
		x++;
	}
}
