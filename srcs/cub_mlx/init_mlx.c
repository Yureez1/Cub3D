/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:01:02 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/20 14:28:38 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int    init_window(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (perror("Failed to initialize mlx"), 1);
    game->mlx_win = mlx_new_window(game->mlx, WIDTH, HEIGHT,"Cub3D Window");
    game->mlx_img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    if (!game->mlx_win || !game->mlx_img)
    {
		mlx_destroy_window(game->mlx, game->mlx_win);
        return (perror("Failed to create window"), 1);
    }
	game->data = mlx_get_data_addr(game->mlx_img, &game->bpp, &game->size_line, &game->endian);
    return (0);
}

void    destroy_mlx(t_game *game)
{
    if (!game || !game->mlx)
        return ;
    if (game->mlx_win)
    {
        mlx_destroy_window(game->mlx, game->mlx_win);
        game->mlx_win = NULL;
    }
    mlx_destroy_display(game->mlx);
    free(game->mlx);
    game->mlx = NULL;
    game->mlx_win = NULL;
}

void    destroy_map(t_map *map)
{
    int    y;

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
