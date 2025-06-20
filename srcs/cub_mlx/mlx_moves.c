/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:09:21 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/20 15:54:02 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
	printf("Moved backward to (%.2f, %.2f)\n", map->player_x, map->player_y);
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
	printf("Moved left to (%.2f, %.2f)\n", map->player_x, map->player_y);
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
	printf("Moved right to (%.2f, %.2f)\n", map->player_x, map->player_y);
}

void	rotate_left(t_map *map)
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
	printf("Rotated right to (%.2f, %.2f)\n", map->player_x, map->player_y);
}

void	rotate_right(t_map *map)
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
	printf("Rotated left to (%.2f, %.2f)\n", map->player_x, map->player_y);
}

void	redraw(t_map *map)
{
	t_rect	player_rect;

	ft_bzero(map->game->data, WIDTH * HEIGHT * 4);
	draw_minimap(map);
	// Dessiner le joueur
	player_rect.x = (int)(map->player_x * TILE_SIZE) - PLAYER_SIZE / 2;
	player_rect.y = (int)(map->player_y * TILE_SIZE) - PLAYER_SIZE / 2;
	player_rect.size = PLAYER_SIZE;
	player_rect.color = 0x00FF00; // vert
	draw_square(player_rect, map->game);
	set_direction(map); // Ligne rouge pour direction du joueur
	mlx_put_image_to_window(map->game->mlx, map->game->mlx_win,
		map->game->mlx_img, 0, 0);
}

int	handle_keypress(int keycode, t_map *map)
{
	if (keycode == 65307)
		exit(0);
	else if (keycode == 'w' || keycode == 119)
		move_forward(map);
	else if (keycode == 's' || keycode == 115)
		move_backward(map);
	else if (keycode == 'a' || keycode == 97)
		move_left(map);
	else if (keycode == 'd' || keycode == 100)
		move_right(map);
	else if (keycode == 65361)
		rotate_left(map);
	else if (keycode == 65363)
		rotate_right(map);
	redraw(map); // 👈 met à jour l’image
	return (0);
}
