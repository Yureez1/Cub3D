/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:46:12 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/17 10:48:34 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int parse_char(char c)
{
if ((c >= 9 && c <= 13) || c == '0' || c == '1' || c == ' ' ||
	c == 'N' || c == 'S' || c == 'E' || c == 'W')
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

int check_invalid_char(t_map *map)
{
    int x;
    int y;

    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width && map->map[y][x])
        {
            if (parse_char(map->map[y][x]))
            {
                perror("Invalid character in map");
                return (1);
            }
            x++;
        }
        y++;
    }
    return (0);
}
