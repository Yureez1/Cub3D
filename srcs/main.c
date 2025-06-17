/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:33:11 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/17 11:10:32 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

int	init_window(void *mlx, void **mlx_win)
{
	mlx = mlx_init();
	if (!mlx)
		return (perror("Failed to initialize mlx"), 1);
	*mlx_win = mlx_new_window(mlx, 800, 600, "Cub3D Window");
	if (!*mlx_win)
	{
		mlx_destroy_window(mlx, *mlx_win);
		return (perror("Failed to create window"), 1);
	}
	mlx_loop(mlx);
	return (0);
}

void	destroy_map(t_map *map)
{
	int	y;

	if (!map || !map->map)
		return ;
	y = 0;
	while (y < map->height)
	{
		free(map->map[y]);
		y++;
	}
	free(map->map);
	map->map = NULL;
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
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
		free(map);
		return (EXIT_FAILURE);
	}
	if (init_window(&mlx, &mlx_win) != 0)
	{
		destroy_map(map);
		free(map);
		return (EXIT_FAILURE);
	}
	destroy_map(map);
	free(map);
	return (0);
}
