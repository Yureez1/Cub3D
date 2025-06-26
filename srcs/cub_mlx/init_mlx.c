/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:01:02 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/26 14:46:11 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (perror("Failed to initialize mlx"), 1);
	game->mlx_win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D Window");
	game->mlx_img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->mlx_win || !game->mlx_img)
	{
		mlx_destroy_window(game->mlx, game->mlx_win);
		return (perror("Failed to create window"), 1);
	}
	game->data = mlx_get_data_addr(game->mlx_img, &game->bpp, &game->size_line,
			&game->endian);
	return (0);
}

void	destroy_mlx(t_game *game)
{
	if (!game || !game->mlx)
		return ;
	if (game->mlx_img)
	{
		mlx_destroy_image(game->mlx, game->mlx_img);
		game->mlx_img = NULL;
	}
	if (game->mlx_win)
	{
		mlx_destroy_window(game->mlx, game->mlx_win);
		game->mlx_win = NULL;
	}
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	game->mlx = NULL;
}

void	free_map_grid(t_map *map)
{
	int	y;

	if (!map || !map->map)
		return ;
	y = 0;
	while (y < map->height)
	{
		if (map->map[y])
			free(map->map[y]);
		y++;
	}
	free(map->map);
	map->map = NULL;
}

void	destroy_map(t_map *map)
{
	if (!map)
		return ;
	free_map_grid(map);
	if (map->game)
	{
		destroy_mlx(map->game);
		free(map->game);
		map->game = NULL;
	}
	if (map->textures)
	{
		destroy_textures(map->textures);
		map->textures = NULL;
	}
	free(map);
}
