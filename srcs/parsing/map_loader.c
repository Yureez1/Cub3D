/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:50:52 by leaugust          #+#    #+#             */
/*   Updated: 2025/06/14 22:08:23 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	open_map_file(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (-1);
	}
	printf("File '%s' opened successfully, fd=%d\n", file_path, fd);
	return (fd);
}

char	**allocate_temp_map(void)
{
	char	**temp_map;

	temp_map = malloc(sizeof(char *) * 1024);
	if (!temp_map)
	{
		perror("Malloc failed for temp_map");
		return (NULL);
	}
	printf("Temporary map allocated.\n");
	return (temp_map);
}

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

int	fill_temp_map(int fd, char **temp_map, int *height, int *max_width)
{
	char	*line;
	int		started;

	started = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!started)
		{
			if (line[0] == ' ' || line[0] == '1')
				started = 1;
			else
			{
				free(line);
				line = get_next_line(fd);
				continue ;
			}
		}
		if (process_map_line(line, temp_map, height, max_width))
			return (free(line), 1);
		free(line);
		line = get_next_line(fd);
	}
	printf("Total lines read: %d, max width: %d\n", *height, *max_width);
	return (0);
}

int	finalize_map(t_map *map, char **temp_map)
{
	int	i;
	int	j;

	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
		return (perror("Malloc failed for final map"), 1);
	i = 0;
	while (i < map->height)
	{
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
		i++;
	}
	map->map[i] = NULL;
	free(temp_map);
	printf("Map finalized: height=%d, width=%d\n", map->height, map->width);
	return (0);
}

int	read_map_lines(int fd, t_map *map)
{
	char	**temp_map;
	int		max_width;
	int		height;

	max_width = 0;
	height = 0;
	temp_map = allocate_temp_map();
	if (!temp_map)
		return (1);
	if (fill_temp_map(fd, temp_map, &height, &max_width))
		return (1);
	map->height = height;
	map->width = max_width;
	if (finalize_map(map, temp_map))
		return (1);
	return (0);
}
