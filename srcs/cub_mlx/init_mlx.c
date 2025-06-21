/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:01:02 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/21 11:42:22 by jbanchon         ###   ########.fr       */
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

void	start_game_loop(t_map *map)
{
	t_game	*game;
	t_rect	rect;

	game = map->game;
	if (!map || !map->game)
		return ;
	rect.x = (int)(map->player_x * TILE_SIZE);
	rect.y = (int)(map->player_y * TILE_SIZE);
	rect.size = PLAYER_SIZE;
	rect.color = 0xFF0000;
	redraw(map);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->mlx_img, 0, 0);
	mlx_hook(game->mlx_win, 2, 1L << 0, handle_keypress, map);
	mlx_hook(game->mlx_win, 3, 1L << 1, handle_keyrelease, map);
	mlx_loop_hook(game->mlx, game_loop, map);
	mlx_loop(game->mlx);
}

void	destroy_mlx(t_game *game)
{
	if (!game || !game->mlx)
		return ;
	if (game->mlx_win)
	{
		mlx_destroy_window(game->mlx, game->mlx_win);
		game->mlx_win = NULL;
	}
	mlx_destroy_display(game->mlx);
	free(game->key);
	free(game->mlx);
	game->mlx = NULL;
	game->mlx_win = NULL;
}

void	destroy_map(t_map *map)
{
	int	y;

	if (!map || !map->map)
		return ;
	if (map->map)
	{
		y = 0;
		while (y < map->height)
		{
			free(map->map[y]);
			y++;
		}
	}
	free(map->map);
	map->map = NULL;
	if (map->game)
		destroy_mlx(map->game);
	destroy_textures(map->textures);
}
