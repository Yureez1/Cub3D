/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:33:11 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/10 13:11:21 by jbanchon         ###   ########.fr       */
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
		free(map);
		return (EXIT_FAILURE);
	}
	printf("Je segfault\n");
	if (init_window(&mlx, &mlx_win) != 0)
	{
		free(map);
		return (EXIT_FAILURE);
	}
	free(map);
	return (0);
}
