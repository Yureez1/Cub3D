/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 21:28:20 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/16 20:29:48 by jbanchon         ###   ########.fr       */
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
    {
        printf("Error: Invalid character in map\n");
        return (1);
    }
    if (check_single_player(map))
    {
        printf("Error: Invalid player position\n");
        return (1);
    }
	if (validate_void_surroundings(map))
	{
		printf("Error: map not closed (0 or player touches space)\n");
		return (1);
	}
	printf("Void surroundings validated.\n");
	fill_voids_with_walls(map);
	printf("Map after filling:\n");
	print_map(map);
	return (0);
}
