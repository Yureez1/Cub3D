/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:33:11 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/18 11:20:51 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

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
