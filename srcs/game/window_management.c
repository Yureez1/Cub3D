/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:18:58 by leaugust          #+#    #+#             */
/*   Updated: 2025/06/26 20:19:24 by leaugust         ###   ########.fr       */
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
	if (!game->data)
	{
		mlx_destroy_image(game->mlx, game->mlx_img);
		mlx_destroy_window(game->mlx, game->mlx_win);
		return (perror("Failed to get image data"), 1);
	}
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
