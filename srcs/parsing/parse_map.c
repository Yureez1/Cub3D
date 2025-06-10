/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:50:26 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/10 15:42:30 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	init_struct(t_map *map)
{
	map->map = NULL;
	map->x = 0;
	map->y = 0;
	map->width = 0;
	map->height = 0;
	map->player_x = -1;
	map->player_y = -1;
	return (0);
}

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

// int	store_map_line(char **temp_map, char *line, int *max_width,
// int line_count)
// {
// 	int	len;

// 	len = ft_strlen(line);
// 	if (line[len - 1] == '\n')
// 		line[len - 1] = '\0';
// 	if ((int)ft_strlen(line) > *max_width)
// 		*max_width = ft_strlen(line);
// 	temp_map[line_count] = ft_strdup(line);
// 	if (!temp_map[line_count])
// 	{
// 		perror("Failed to duplicate line");
// 		return (1);
// 	}
// 	return (0);
// }

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

int	fill_temp_map(int fd, char **temp_map, int *height, int *max_width)
{
	char	*line;
	int		line_len;
	int		started;

	started = 0;
	line = NULL;
	while ((line = get_next_line(fd, line)))
	{
		line_len = ft_strlen(line);
		if (!started)
		{
			if (line[0] == ' ' || line[0] == '1')
				started = 1;
			else
			{
				free(line);
				continue ;
			}
		}
		if (line[line_len - 1] == '\n')
			line[line_len - 1] = '\0';
		if ((int)ft_strlen(line) > *max_width)
			*max_width = ft_strlen(line);
		temp_map[*height] = ft_strdup(line);
		if (!temp_map[*height])
		{
			perror("Strdup failed");
			free(line);
			return (1);
		}
		/*printf("Line %d read: \"%s\" (length=%d)\n", *height,
			temp_map[*height],
			(int)ft_strlen(temp_map[*height]));*/
		(*height)++;
		free(line);
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
		free(temp_map[i]); // libère l'ancienne ligne copiée
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

int	parse_map(t_map *map, char *file_path)
{
	int	fd;

	printf("=== Starting map parsing ===\n");
	fd = open_map_file(file_path);
	if (fd < 0)
	{
		printf("Error: Failed to open file %s\n", file_path);
		return (1);
	}
	printf("Successfully opened %s (fd=%d)\n", file_path, fd);
	if (read_map_lines(fd, map))
	{
		printf("Error reading map lines\n");
		close(fd);
		return (1);
	}
	close(fd);
	printf("Map reading complete - Dimensions: %dx%d\n", map->width,
		map->height);
	if (validate_map(map))
	{
		printf("Error: Map validation failed\n");
		return (1);
	}
	printf("Map validated successfully\n");
	if (find_player_position(map))
	{
		printf("Error: Player position not found\n");
		return (1);
	}
	printf("Player found at (%d, %d) facing %c\n", map->player_x, map->player_y,
		map->player_dir);
	printf("=== Map parsing completed successfully ===\n");
	return (0);
}
