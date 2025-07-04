/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:10:55 by leaugust          #+#    #+#             */
/*   Updated: 2025/07/04 13:02:52 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	parse_char(char c)
{
	if ((c >= 9 && c <= 13) || c == '0' || c == '1' || c == ' ' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W')
		return (0);
	else if (c == '\n')
		return (1);
	else
	{
		fprintf(stderr, "Error: Invalid character '%c' in map\n", c);
		return (1);
	}
	return (0);
}

// int	check_surroundings(t_map *map, int x, int y)
// {
// 	return (is_hole(map, x - 1, y) || is_hole(map, x + 1, y) || is_hole(map, x,
// 			y - 1) || is_hole(map, x, y + 1));
// }

// int	is_hole(t_map *map, int x, int y)
// {
// 	if (y < 0 || y >= map->height || x < 0)
// 		return (1);
// 	if (x >= (int)ft_strlen(map->map[y]))
// 		return (1);
// 	if (map->map[y][x] == ' ')
// 		return (1);
// 	return (0);
// }

// int check_border()
