/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:33:09 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/21 15:17:16 by jbanchon         ###   ########.fr       */
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

# define WIDTH 1280
# define HEIGHT 1080
# define MOVE_SPEED 0.15
# define ROTATE_SPEED 0.05
# define TILE_SIZE 25
# define PLAYER_SIZE 25
# define RAY_STEP (1.0 / TILE_SIZE)

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef enum e_action
{
	MOVE_FWD,
	MOVE_BWD,
	MOVE_LEFT,
	MOVE_RIGHT,
	ROTATE_LEFT,
	ROTATE_RIGHT,
	COUNT_ACT
}					t_action;

typedef struct s_textures
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*floor;
	char			*ceiling;
	int				floor_rgb;
	int				ceiling_rgb;

}					t_textures;

typedef struct s_game
{
	void			*mlx;
	void			*mlx_win;
	void			*mlx_img;
	int				bpp;
	int				size_line;
	char			*data;
	int				endian;
	int				key[COUNT_ACT];
}					t_game;

typedef struct s_rect
{
	int				x;
	int				y;
	int				size;
	int				color;
}					t_rect;

typedef struct s_map
{
	char			**map;
	int				x;
	int				y;
	int				width;
	int				height;
	double			player_x;
	double			player_y;
	char			player_dir;
	double			player_angle;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	struct s_game	*game;
	t_textures		*textures;
}					t_map;

int					touch(t_map *map, double ray_x, double ray_y);

/*==== calculate_vector.c ====*/

void				accumulate_vector(t_map *map, double *v_x, double *v_y);
void				normalize_vector(double *v_x, double *v_y);
void				calc_move_vector(t_map *map, double *v_x, double *v_y);
void				rotate_left(t_map *map);
void				rotate_right(t_map *map);

/*==== game_loop.c ====*/

void				start_game_loop(t_map *map);
int					game_loop(t_map *map);
void				redraw(t_map *map);

/*==== main.c ====*/

void				put_pixel(int x, int y, int color, t_game *game);
void				draw_square(t_rect rect, t_game *game);
void				draw_minimap(t_map *map);
void				set_direction(t_map *map);

/*==== init_mlx.c ====*/

int					init_window(t_game *game);
void				destroy_map(t_map *map);
void				destroy_mlx(t_game *game);

/*==== mlx_moves.c ====*/

int					is_walkable(t_map *map, double x, double y);
void				apply_move(t_map *map, double v_x, double v_y);
void				apply_rotation(t_map *map);
int					handle_keypress(int keycode, t_map *map);
int					handle_keyrelease(int keycode, t_map *map);

/*==== init_struct.c ====*/

int					init_textures(t_textures *textures);
int					init_struct(t_map *map);
int					init_game_struct(t_game *game);

/*==== map_checker.c ====*/

int					is_out_of_bounds(int x, int y, int width, int height);
int					is_touching_void(t_map *map, int x, int y);
int					validate_void_surroundings(t_map *map);
void				fill_voids_with_walls(t_map *map);

/*==== map_loader.c ====*/

int					open_map_file(char *file_path);
char				**allocate_temp_map(void);
int					process_map_line(char *line, char **temp_map, int *height,
						int *max_width);
int					fill_temp_map(int fd, char **temp_map, int *height,
						int *max_width);
int					finalize_map(t_map *map, char **temp_map);
int					read_map_lines(int fd, t_map *map);

/*==== map_parser.c ====*/

int					parse_map(t_map *map, char *file_path);

/*==== map_textures.c ====*/

int					handle_texture_line(t_textures *textures, char *line);
int					handle_color_line(t_textures *textures, char *line);
int					parse_line(t_textures *textures, char *line);
int					check_textures(t_textures *textures);
int					parse_textures_colors(t_textures *textures,
						char *file_path);
int					destroy_textures(t_textures *textures);
int					convert_rgb(unsigned int r, unsigned int g, unsigned int b);
int					parse_rgb(const char *str, int *res);
int					check_xpm_file(const char *file_path);
int					check_exist_textures(t_textures *textures);

/*==== parse_char.c ====*/

int					check_invalid_char(t_map *map);

/*==== player_pos.c ====*/

int					init_player_dir(t_map *map);
int					check_single_player(t_map *map);
int					set_player_position(t_map *map, int x, int y);
int					find_player_position(t_map *map);

/*==== print_map.c ====*/

int					validate_map(t_map *map);

#endif