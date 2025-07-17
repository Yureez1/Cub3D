/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:33:09 by jbanchon          #+#    #+#             */
/*   Updated: 2025/07/17 14:08:38 by leaugust         ###   ########.fr       */
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

# define NB_TEXTURES 4
# define WIDTH 1280
# define HEIGHT 720
# define MOVE_SPEED 0.02
# define ROTATE_SPEED 0.02
# define TILE_SIZE 64
# define PLAYER_SIZE 10
# define PI 3.141592653589793
# define FOV 1.0471975
# define MINIMAP_SCALE 12
# define MINIMAP_PADDING 10

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

enum				e_tex_index
{
	TEX_NO = 0,
	TEX_SO,
	TEX_WE,
	TEX_EA,
};

typedef struct s_bounds
{
	int				left_cell;
	int				right_cell;
	int				top_cell;
	int				bottom_cell;
}					t_bounds;

typedef struct s_texpath
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*floor;
	char			*ceiling;
	int				floor_rgb;
	int				ceiling_rgb;
}					t_texpath;

typedef struct s_textures
{
	void			*img;
	int				*data;
	int				width;
	int				height;
	int				bpp;
	int				line_size;
	int				endian;

}					t_textures;

typedef struct s_game
{
	void			*mlx;
	void			*mlx_win;
	void			*mlx_img;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
	int				key[COUNT_ACT];
	t_textures		textures[NB_TEXTURES];
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
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			player_angle;
	int				player_dir;
	struct s_game	*game;
	t_textures		*textures;
	t_texpath		*texpath;
	int				floor_color;
	int				ceiling_color;
}					t_map;

typedef struct s_ray
{
	double			dir_x;
	double			dir_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				side;
	int				line_h;
	int				draw_s;
	int				draw_end;
	double			perp_dist;
	double			step_tex;
	double			tex_pos;
	int				ty;
	char			*row;
	int				color;
	int				y;
}					t_ray;

/*==== game_loop.c ====*/

int					close_window(t_map *map);
void				start_game_loop(t_map *map);
int					game_loop(t_map *map);

/*==== input_handling.c ====*/

int					handle_keypress(int keycode, t_map *map);
int					handle_keyrelease(int keycode, t_map *map);

/*==== map_management.c ====*/

void				destroy_map(t_map *map);

/*==== move_vector.c ====*/

void				calc_move_vector(t_map *map, double *v_x, double *v_y);

/*==== move.c ====*/

void				apply_move(t_map *map, double v_x, double v_y);
void				apply_rotation(t_map *map);

/*==== window_management.c ====*/

int					init_window(t_game *game);
void				destroy_mlx(t_game *game);

/* INIT */

/*==== init_directions.c ====*/

int					init_player_dir(t_map *map);

/*==== init_structs.c ====*/

int					init_struct(t_map *map);

/* PARSING */

/*==== char_validation.c ====*/

int					parse_char(char c);

/*==== map_utils.c ====*/

int					process_map_line(char *line, char **temp_map, int *height,
						int *max_width);
int					finalize_map(t_map *map, char **temp_map);

/*==== map_validation.c ====*/

int					validate_map(t_map *map);

/*==== parse_map.c ====*/

int					parse_map(t_map *map, char *file_path);

/*==== player_init.c ====*/

int					set_player_position(t_map *map, int x, int y);
void				fill_voids_with_walls(t_map *map);

/*==== void_check.c ====*/

int					is_touching_void(t_map *map, int x, int y);

/*==== line_check.c ====*/

void				free_temp_map(char **temp_map);
int					is_line_empty(char *line);
int					handle_pre_map_line(char *line, int *started);
int					handle_map_line(char *line, char **temp_map, int *height,
						int *max_width);

/* RAYCASTING */

/*==== raycasting.c ====*/

int					perform_dda(t_map *map, t_ray *ray);

/*==== raycaster.c ====*/

void				render_walls(t_map *map);

/*==== render_walls.c ====*/

void				put_pixel(int x, int y, int color, t_game *game);

/*==== ray_init.c ====*/

void				init_ray(t_map *map, t_ray *ray, int x);

/*==== ray_projection.c ====*/

void				calc_projection(t_map *map, t_ray *ray);
int					compute_texx(t_map *map, t_ray *ray);

/*==== ray_texture.c ====*/

int					select_texture(t_ray *ray);
void				draw_column(t_map *map, t_ray *ray, int x);

/* TEXTURES */

/*==== load_textures.c*/

int					load_textures(t_map *map);

/*==== parse_textures.c ====*/

int					parse_textures_colors(t_texpath *texpath, char *file_path);

/*==== rgb_utils.c ====*/

int					parse_rgb(const char *str, int *res);
int					check_exist_textures(t_texpath *texpath);
int					check_xpm_file(const char *file_path);

/*==== texture_utils.c ====*/

int					handle_ceiling(t_texpath *texpath, char *line);
int					handle_floor(t_texpath *texpath, char *line);
int					destroy_texpath(t_texpath *texpath);
int					is_valid_number(const char *str);
int					has_leading_zero(const char *str);

/*==== parse_utils.c ====*/

int					handle_color_line(t_texpath *texpath, char *line);
int					handle_texture_line(t_texpath *texpath, char *line);

#endif