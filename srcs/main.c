/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:33:11 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/26 17:14:30 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(*map));
	if (!map)
		return (perror("Failed to allocate memory for map"), EXIT_FAILURE);
	if (argc != 2)
		return (perror("Usage: ./cub3d <map_file>"), EXIT_FAILURE);
	init_struct(map);
	if (parse_map(map, argv[1]) != 0)
	{
		destroy_map(map);
		return (EXIT_FAILURE);
	}
	if (init_window(map->game) != 0)
	{
		destroy_map(map);
		return (EXIT_FAILURE);
	}
	start_game_loop(map);
	destroy_map(map);
	free(map->game);
	free(map);
	return (0);
}
