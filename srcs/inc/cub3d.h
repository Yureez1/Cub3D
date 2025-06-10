/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:33:09 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/10 15:41:50 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../libft/libft.h"
# include "../../mlx/mlx.h"
# include "../gnl/get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_textures
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*floor;
	char	*ceiling;

}			t_textures;

typedef struct s_map
{
	char	**map;
	int		x;
	int		y;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
	double	player_angle;
}			t_map;

int			parse_map(t_map *map, char *file_path);
int			read_map_lines(int fd, t_map *map);
int			finalize_map(t_map *map, char **temp_map);
int			fill_temp_map(int fd, char **temp_map, int *height, int *max_width);
char		**allocate_temp_map(void);
int			store_map_line(char **temp_map, char *line, int *max_width,
				int line_count);
int			open_map_file(char *file_path);
int			init_struct(t_map *map);

int	find_player_position(t_map *map);
int	set_player_position(t_map *map, int x, int y);

int	validate_map(t_map *map);
void	fill_voids_with_walls(t_map *map);
int	validate_void_surroundings(t_map *map);
int	is_touching_void(char **map, int x, int y, int width, int height);
int	is_out_of_bounds(int x, int y, int width, int height);


#endif