/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:33:09 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/06 11:45:24 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../mlx/mlx.h"
# include "../../get_next_line.h"
# include "../../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

struct		s_map
{
	char	**map;
	int		x;
	int		y;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
}			t_map;

#endif