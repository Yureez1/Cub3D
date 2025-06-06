/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:33:11 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/05 14:02:34 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

int main(void)
{
    void *mlx;
    void *mlx_win;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 800, 600, "Cub3D Window");
    mlx_loop(mlx);
}
