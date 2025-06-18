/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:33:09 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/18 15:09:19 by jbanchon         ###   ########.fr       */
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
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*floor;
	char		*ceiling;
	int			floor_rgb;
	int			ceiling_rgb;

}				t_textures;

typedef struct s_map
{
	char		**map;
	int			x;
	int			y;
	int			width;
	int			height;
	double		player_x;
	double		player_y;
	char		player_dir;
	double		player_angle;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	void		*mlx;
	void		*mlx_win;
	t_textures	*textures;
}				t_map;

/*==== init_mlx.c ====*/

int				init_window(void *mlx, void **mlx_win);
void			destroy_mlx(t_map *map);
void			destroy_map(t_map *map);

/*==== mlx_moves.c ====*/

/*==== init_struct.c ====*/

int				init_textures(t_textures *textures);
int				init_struct(t_map *map);

/*==== map_checker.c ====*/

int				is_out_of_bounds(int x, int y, int width, int height);
int				is_touching_void(t_map *map, int x, int y);
int				validate_void_surroundings(t_map *map);
void			fill_voids_with_walls(t_map *map);

/*==== map_loader.c ====*/

int				open_map_file(char *file_path);
char			**allocate_temp_map(void);
int				process_map_line(char *line, char **temp_map, int *height,
					int *max_width);
int				fill_temp_map(int fd, char **temp_map, int *height,
					int *max_width);
int				finalize_map(t_map *map, char **temp_map);
int				read_map_lines(int fd, t_map *map);

/*==== map_parser.c ====*/

int				parse_map(t_map *map, char *file_path);

/*==== map_textures.c ====*/

int				handle_texture_line(t_textures *textures, char *line);
int				handle_color_line(t_textures *textures, char *line);
int				parse_line(t_textures *textures, char *line);
int				check_textures(t_textures *textures);
int				parse_textures_colors(t_textures *textures, char *file_path);
int				destroy_textures(t_textures *textures);
int				convert_rgb(unsigned int r, unsigned int g, unsigned int b);
int				parse_rgb(const char *str, int *res);
int				check_xpm_file(const char *file_path);
int				check_exist_textures(t_textures *textures);

/*==== parse_char.c ====*/

int				check_invalid_char(t_map *map);

/*==== player_pos.c ====*/

int				init_player_dir(t_map *map);
int				check_single_player(t_map *map);
int				set_player_position(t_map *map, int x, int y);
int				find_player_position(t_map *map);

/*==== print_map.c ====*/

int				validate_map(t_map *map);

#endif