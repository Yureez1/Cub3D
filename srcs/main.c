/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:33:11 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/20 15:53:20 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_map	*map;
	t_game	*game;
	t_rect	rect;

	map = (t_map *)malloc(sizeof(*map));
	if (!map)
		return (perror("Failed to allocate memory for map"), EXIT_FAILURE);
	if (argc != 2)
		return (perror("Usage: ./cub3d <map_file>"), EXIT_FAILURE);
	game = (t_game *)malloc(sizeof(*game));
	if (!game)
	{
		free(map);
		return (perror("Failed to allocate memory for game"), EXIT_FAILURE);
	}
	map->game = game;
	init_struct(map);
	if (parse_map(map, argv[1]) != 0)
	{
		destroy_map(map);
		free(game);
		free(map);
		return (EXIT_FAILURE);
	}
	if (init_window(game) != 0)
	{
		destroy_map(map);
		free(game);
		free(map);
		return (EXIT_FAILURE);
	}
	rect.x = (int)(map->player_x * TILE_SIZE);
	rect.y = (int)(map->player_y * TILE_SIZE);
	rect.size = PLAYER_SIZE; // ou 10 selon ce que tu veux
	rect.color = 0x00FF00;
	redraw(map);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->mlx_img, 0, 0);
	mlx_hook(map->game->mlx_win, 2, 1L << 0, handle_keypress, map);
	mlx_loop(map->game->mlx);
	destroy_map(map);
	free(game);
	free(map);
	return (0);
}
