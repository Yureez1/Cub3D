/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:09:21 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/21 11:55:45 by jbanchon         ###   ########.fr       */
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

// void	move_forward(t_map *map)
// {
// 	double	new_x;
// 	double	new_y;

// 	new_x = map->player_x + map->dir_x * MOVE_SPEED;
// 	new_y = map->player_y + map->dir_y * MOVE_SPEED;
// 	if (is_walkable(map, new_x, map->player_y))
// 		map->player_x = new_x;
// 	if (is_walkable(map, map->player_x, new_y))
// 		map->player_y = new_y;
// 	printf("Moved forward to (%.2f, %.2f)\n", map->player_x, map->player_y);
// }

// void	move_backward(t_map *map)
// {
// 	double	new_x;
// 	double	new_y;

// 	new_x = map->player_x - map->dir_x * MOVE_SPEED;
// 	new_y = map->player_y - map->dir_y * MOVE_SPEED;
// 	if (is_walkable(map, new_x, map->player_y))
// 		map->player_x = new_x;
// 	if (is_walkable(map, map->player_x, new_y))
// 		map->player_y = new_y;
// 	printf("Moved backward to (%.2f, %.2f)\n", map->player_x, map->player_y);
// }

// void	move_left(t_map *map)
// {
// 	double	new_x;
// 	double	new_y;

// 	new_x = map->player_x - map->plane_x * MOVE_SPEED;
// 	new_y = map->player_y - map->plane_y * MOVE_SPEED;
// 	if (is_walkable(map, new_x, map->player_y))
// 		map->player_x = new_x;
// 	if (is_walkable(map, map->player_x, new_y))
// 		map->player_y = new_y;
// 	printf("Moved left to (%.2f, %.2f)\n", map->player_x, map->player_y);
// }

// void	move_right(t_map *map)
// {
// 	double	new_x;
// 	double	new_y;

// 	new_x = map->player_x + map->plane_x * MOVE_SPEED;
// 	new_y = map->player_y + map->plane_y * MOVE_SPEED;
// 	if (is_walkable(map, new_x, map->player_y))
// 		map->player_x = new_x;
// 	if (is_walkable(map, map->player_x, new_y))
// 		map->player_y = new_y;
// 	printf("Moved right to (%.2f, %.2f)\n", map->player_x, map->player_y);
// }

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

static void	calc_move_vector(t_map *map, double *v_x, double *v_y)
{
	t_game	*game;
	double	mag;

	game = map->game;
	*v_x = 0;
	*v_y = 0;
	if (game->key[MOVE_FWD])
	{
		*v_x += map->dir_x * MOVE_SPEED;
		*v_y += map->dir_y * MOVE_SPEED;
	}
	if (game->key[MOVE_BWD])
	{
		*v_x -= map->dir_x * MOVE_SPEED;
		*v_y -= map->dir_y * MOVE_SPEED;
	}
	if (game->key[MOVE_LEFT])
	{
		*v_x -= map->plane_x * MOVE_SPEED;
		*v_y -= map->plane_y * MOVE_SPEED;
	}
	if (game->key[MOVE_RIGHT])
	{
		*v_x += map->plane_x * MOVE_SPEED;
		*v_y += map->plane_y * MOVE_SPEED;
	}
	mag = sqrt((*v_x) * (*v_x) + (*v_y) * (*v_y));
	if (mag > 0.0)
	{
		*v_x = (*v_x / mag) * MOVE_SPEED;
		*v_y = (*v_y / mag) * MOVE_SPEED;
	}
}

static void	apply_move(t_map *map, double v_x, double v_y)
{
	if (is_walkable(map, map->player_x + v_x, map->player_y))
		map->player_x += v_x;
	if (is_walkable(map, map->player_x, map->player_y + v_y))
		map->player_y += v_y;
}

static void	apply_rotation(t_map *map)
{
	t_game	*game;

	game = map->game;
	if (game->key[ROTATE_LEFT])
		rotate_left(map);
	else if (game->key[ROTATE_RIGHT])
		rotate_right(map);
}

void	redraw(t_map *map)
{
	t_rect	player_rect;

	ft_bzero(map->game->data, WIDTH * HEIGHT * 4);
	draw_minimap(map);
	player_rect.x = (int)(map->player_x * TILE_SIZE) - PLAYER_SIZE / 2;
	player_rect.y = (int)(map->player_y * TILE_SIZE) - PLAYER_SIZE / 2;
	player_rect.size = PLAYER_SIZE;
	player_rect.color = 0x00FF00;
	draw_square(player_rect, map->game);
	set_direction(map);
	mlx_put_image_to_window(map->game->mlx, map->game->mlx_win,
		map->game->mlx_img, 0, 0);
}

int	handle_keypress(int keycode, t_map *map)
{
	t_game	*game;

	game = map->game;
	if (keycode == KEY_ESC)
	{
		destroy_map(map);
		exit(0);
	}
	else if (keycode == KEY_W)
		game->key[MOVE_FWD] = 1;
	else if (keycode == KEY_S)
		game->key[MOVE_BWD] = 1;
	else if (keycode == KEY_A)
		game->key[MOVE_LEFT] = 1;
	else if (keycode == KEY_D)
		game->key[MOVE_RIGHT] = 1;
	else if (keycode == KEY_LEFT)
		game->key[ROTATE_LEFT] = 1;
	else if (keycode == KEY_RIGHT)
		game->key[ROTATE_RIGHT] = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_map *map)
{
	t_game	*game;

	game = map->game;
	if (keycode == KEY_W)
		game->key[MOVE_FWD] = 0;
	else if (keycode == KEY_S)
		game->key[MOVE_BWD] = 0;
	else if (keycode == KEY_A)
		game->key[MOVE_LEFT] = 0;
	else if (keycode == KEY_D)
		game->key[MOVE_RIGHT] = 0;
	else if (keycode == KEY_LEFT)
		game->key[ROTATE_LEFT] = 0;
	else if (keycode == KEY_RIGHT)
		game->key[ROTATE_RIGHT] = 0;
	return (0);
}

int	game_loop(t_map *map)
{
	double	v_x;
	double	v_y;

	calc_move_vector(map, &v_x, &v_y);
	apply_move(map, v_x, v_y);
	apply_rotation(map);
	redraw(map);
	return (0);
}
