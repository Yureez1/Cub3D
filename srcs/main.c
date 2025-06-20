/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:33:11 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/20 14:27:33 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	i;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	i = y * game->size_line + x * (game->bpp / 8);
	game->data[i] = (color & 0xFF);
	game->data[i + 1] = (color >> 8) & 0xFF;
	game->data[i + 2] = (color >> 16) & 0xFF;
}

void	draw_square(t_rect rect, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < rect.size)
	{
		j = 0;
		while (j < rect.size)
		{
			put_pixel(rect.x + i, rect.y + j, rect.color, game);
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_game	*game;

	map = (t_map *)malloc(sizeof(*map));
	if (!map)
		return (perror("Failed to allocate memory for map"), EXIT_FAILURE);
	if (argc != 2)
		return (perror("Usage: ./cub3d <map_file>"), EXIT_FAILURE);
	game = (t_game *)malloc(sizeof(*game));
	if (!game)
	{
		free(map);
		return (perror("Failed to allocate memory for game"), EXIT_FAILURE);
	}
	map->game = game;
	init_struct(map);
	if (parse_map(map, argv[1]) != 0)
	{
		destroy_map(map);
		free(game);
		free(map);
		return (EXIT_FAILURE);
	}
	if (init_window(game) != 0)
	{
		destroy_map(map);
		free(game);
		free(map);
		return (EXIT_FAILURE);
	}
	t_rect	rect = {WIDTH / 2, HEIGHT / 2, 10, 0x00FF00};
	draw_square(rect, map->game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->mlx_img, 0, 0);
	mlx_hook(map->game->mlx_win, 2, 1L << 0, handle_keypress, map);
	mlx_loop(map->game->mlx);
	destroy_map(map);
	free(game);
	free(map);
	return (0);
}
