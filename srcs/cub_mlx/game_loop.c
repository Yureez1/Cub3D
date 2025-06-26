/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:03:12 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/26 17:06:36 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	start_game_loop(t_map *map)
{
	t_game	*game;
	t_rect	rect;

	game = map->game;
	if (!map || !map->game)
		return ;
	rect.x = (int)(map->player_x * TILE_SIZE);
	rect.y = (int)(map->player_y * TILE_SIZE);
	rect.size = PLAYER_SIZE;
	rect.color = 0xFF0000;
	redraw(map);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->mlx_img, 0, 0);
	mlx_hook(game->mlx_win, 2, 1L << 0, handle_keypress, map);
	mlx_hook(game->mlx_win, 3, 1L << 1, handle_keyrelease, map);
	mlx_loop_hook(game->mlx, game_loop, map);
	mlx_loop(game->mlx);
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

void	redraw(t_map *map)
{
	// t_rect	player_rect;
	if (!map || !map->game || !map->game->data)
		return ;
	ft_bzero(map->game->data, WIDTH * HEIGHT * 4);
	draw_minimap(map);
	// player_rect.x = (int)(map->player_x * TILE_SIZE) - PLAYER_SIZE / 2;
	// player_rect.y = (int)(map->player_y * TILE_SIZE) - PLAYER_SIZE / 2;
	// player_rect.size = PLAYER_SIZE;
	// player_rect.color = 0x00FF00;
	// draw_square(player_rect, map->game);
	set_direction(map);
	mlx_put_image_to_window(map->game->mlx, map->game->mlx_win,
		map->game->mlx_img, 0, 0);
}
