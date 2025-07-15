/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:03:12 by jbanchon          #+#    #+#             */
/*   Updated: 2025/07/15 15:47:53 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	redraw(t_map *map)
{
	if (!map || !map->game || !map->game->data)
		return ;
	ft_bzero(map->game->data, WIDTH * HEIGHT * 4);
	render_walls(map);
	mlx_put_image_to_window(map->game->mlx, map->game->mlx_win,
		map->game->mlx_img, 0, 0);
}

static void	init_and_load(t_map *map)
{
	t_game	*game;

	game = map->game;
	if (!map || !game)
	{
		printf("Error: Map or game structure is NULL\n");
		exit(EXIT_FAILURE);
	}
	if (init_window(game))
	{
		exit(EXIT_FAILURE);
		destroy_map(map);
	}
	if (load_textures(map))
	{
		printf("Error: Failed to load textures\n");
		destroy_map(map);
		exit(EXIT_FAILURE);
	}
}

int	close_window(t_map *map)
{
	destroy_map(map);
	exit(0);
	return (0);
}

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
	init_and_load(map);
	redraw(map);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->mlx_img, 0, 0);
	mlx_hook(game->mlx_win, 2, 1L << 0, handle_keypress, map);
	mlx_hook(game->mlx_win, 3, 1L << 1, handle_keyrelease, map);
	mlx_hook(game->mlx_win, 17, 0, close_window, map);
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
