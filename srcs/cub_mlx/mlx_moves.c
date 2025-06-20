/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:09:21 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/20 14:16:12 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#define MOVE_SPEED 0.1
#define ROTATE_SPEED 0.05

int	is_walkable(t_map *map, double x, double y)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)x;
	grid_y = (int)y;
	if (grid_x < 0 || grid_x >= map->width || grid_y < 0
		|| grid_y >= map->height)
		return (0);
	return (map->map[grid_y][grid_x] != '1');
}

void	move_forward(t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = map->player_x + map->dir_x * MOVE_SPEED;
	new_y = map->player_y + map->dir_y * MOVE_SPEED;
	if (is_walkable(map, new_x, map->player_y))
		map->player_x = new_x;
	if (is_walkable(map, map->player_x, new_y))
		map->player_y = new_y;
    printf("Moved forward to (%.2f, %.2f)\n", map->player_x, map->player_y);
}

void	move_backward(t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = map->player_x - map->dir_x * MOVE_SPEED;
	new_y = map->player_y - map->dir_y * MOVE_SPEED;
	if (is_walkable(map, new_x, map->player_y))
		map->player_x = new_x;
	if (is_walkable(map, map->player_x, new_y))
		map->player_y = new_y;
}

void	move_left(t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = map->player_x - map->plane_x * MOVE_SPEED;
	new_y = map->player_y - map->plane_y * MOVE_SPEED;
	if (is_walkable(map, new_x, map->player_y))
		map->player_x = new_x;
	if (is_walkable(map, map->player_x, new_y))
		map->player_y = new_y;
}

void	move_right(t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = map->player_x + map->plane_x * MOVE_SPEED;
	new_y = map->player_y + map->plane_y * MOVE_SPEED;
	if (is_walkable(map, new_x, map->player_y))
		map->player_x = new_x;
	if (is_walkable(map, map->player_x, new_y))
		map->player_y = new_y;
}

void	rotate_left(t_map *map)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = map->dir_x;
	old_plane_x = map->plane_x;
	map->dir_x = map->dir_x * cos(ROTATE_SPEED) - map->dir_y
		* sin(ROTATE_SPEED);
	map->dir_y = old_dir_x * sin(ROTATE_SPEED) + map->dir_y * cos(ROTATE_SPEED);
	map->plane_x = map->plane_x * cos(ROTATE_SPEED) - map->plane_y
		* sin(ROTATE_SPEED);
	map->plane_y = old_plane_x * sin(ROTATE_SPEED) + map->plane_y
		* cos(ROTATE_SPEED);
}

void	rotate_right(t_map *map)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = map->dir_x;
	old_plane_x = map->plane_x;
	map->dir_x = map->dir_x * cos(-ROTATE_SPEED) - map->dir_y
		* sin(-ROTATE_SPEED);
	map->dir_y = old_dir_x * sin(-ROTATE_SPEED) + map->dir_y
		* cos(-ROTATE_SPEED);
	map->plane_x = map->plane_x * cos(-ROTATE_SPEED) - map->plane_y
		* sin(-ROTATE_SPEED);
	map->plane_y = old_plane_x * sin(-ROTATE_SPEED) + map->plane_y
		* cos(-ROTATE_SPEED);
}

int	handle_keypress(int keycode, t_map *map)
{
	if (keycode == 65307) // ESC
	{
		destroy_map(map);
		exit(0);
	}
	else if (keycode == 'w' || keycode == 119)
		move_forward(map);
	else if (keycode == 's' || keycode == 115)
		move_backward(map);
	else if (keycode == 'a' || keycode == 97)
		move_left(map);
	else if (keycode == 'd' || keycode == 100)
		move_right(map);
	else if (keycode == 65361) // Left arrow
		rotate_left(map);
	else if (keycode == 65363) // Right arrow
		rotate_right(map);
	return (0);
}
