/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:33:11 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/21 10:38:19 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_map	*map;
	t_game	*game;

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
	start_game_loop(map);
	destroy_map(map);
	free(game);
	free(map);
	return (0);
}
