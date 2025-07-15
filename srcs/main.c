/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:33:11 by jbanchon          #+#    #+#             */
/*   Updated: 2025/07/15 14:44:10 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

static int	has_cub_extension(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	return (ft_strncmp(filename + len - 4, ".cub", 4) == 0);
}

static void	cleanup_and_exit(t_map *map)
{
	destroy_map(map);
}

static t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(*map));
	if (!map)
	{
		printf("Failed to allocate memory for map");
		return (NULL);
	}
	ft_bzero(map, sizeof(*map));
	init_struct(map);
	return (map);
}

static int	check_args(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		return (printf("Usage: ./cub3d <map_file>"), 1);
	if (!has_cub_extension(argv[1]))
		return (printf("Error: File must have .cub extension\n"), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (printf("Error: cannot open file"), 1);
	close(fd);
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	*map;

	if (check_args(argc, argv))
		return (EXIT_FAILURE);
	map = init_map();
	if (!map)
		return (EXIT_FAILURE);
	if (parse_map(map, argv[1]) != 0)
	{
		destroy_map(map);
		return (EXIT_FAILURE);
	}
	start_game_loop(map);
	cleanup_and_exit(map);
	return (0);
}
