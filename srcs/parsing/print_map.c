/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 21:28:20 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/18 13:51:01 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	print_map(t_map *map)
{
	int	y;

	y = 0;
	printf("=== MAP ===\n");
	while (y < map->height)
	{
		printf("%s\n", map->map[y]);
		y++;
	}
	printf("===========\n");
}

int	validate_map(t_map *map)
{
	printf("Map before filling:\n");
	print_map(map);
	if (check_invalid_char(map))
		return (perror("Error: Invalid character in map\n"), 1);
	if (check_single_player(map))
		return (perror("Error: Invalid player position\n"), 1);
	if (find_player_position(map))
		return (perror("Error: Failed to find player position\n"), 1);
	if (init_player_dir(map))
		return (perror("Error: Failed to initialize player direction\n"), 1);
	if (validate_void_surroundings(map))
		return (perror("Error: map not closed (0 or player touches space)\n"),
			1);
	printf("Void surroundings validated.\n");
	fill_voids_with_walls(map);
	printf("Map after filling:\n");
	print_map(map);
	return (0);
}
