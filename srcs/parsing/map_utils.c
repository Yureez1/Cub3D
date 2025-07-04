/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:39:40 by jbanchon          #+#    #+#             */
/*   Updated: 2025/07/04 14:04:18 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	process_map_line(char *line, char **temp_map, int *height, int *max_width)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		line[len - 1] = '\0';
	len = ft_strlen(line);
	if (len > *max_width)
		*max_width = len;
	temp_map[*height] = ft_strdup(line);
	if (temp_map[*height] == NULL)
	{
		perror("Strdup failed");
		free(line);
		return (1);
	}
	(*height)++;
	free(line);
	return (0);
}

int	copy_map_row(t_map *map, char **temp_map, int i)
{
	int	j;

	map->map[i] = malloc(sizeof(char) * (map->width + 1));
	if (!map->map[i])
		return (perror("Malloc failed for final map row"), 1);
	j = 0;
	while (temp_map[i][j])
	{
		map->map[i][j] = temp_map[i][j];
		j++;
	}
	while (j < map->width)
		map->map[i][j++] = ' ';
	map->map[i][j] = '\0';
	free(temp_map[i]);
	return (0);
}

int	finalize_map(t_map *map, char **temp_map)
{
	int	i;

	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
		return (perror("Malloc failed for final map"), 1);
	i = 0;
	while (i < map->height)
	{
		if (copy_map_row(map, temp_map, i))
			return (1);
		i++;
	}
	map->map[i] = NULL;
	free(temp_map);
	printf("Map finalized: height=%d, width=%d\n", map->height, map->width);
	return (0);
}
