/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:33:09 by jbanchon          #+#    #+#             */
/*   Updated: 2025/06/28 15:04:04 by leaugust         ###   ########.fr       */
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
# define MOVE_SPEED 0.1
# define ROTATE_SPEED 0.1
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

/* GAME */
void	draw_floor_ceiling_column(t_map *map, int x, int start, int end);

/*==== collision.c ====*/
int					touch(t_map *map, double ray_x, double ray_y);

/*==== game_loop.c ====*/

int					close_window(t_map *map);
void				start_game_loop(t_map *map);
int					game_loop(t_map *map);
void				redraw(t_map *map);

/*==== input_handling.c ====*/

int					handle_keypress(int keycode, t_map *map);
int					handle_keyrelease(int keycode, t_map *map);

/*==== map_management.c ====*/

void				free_map_grid(t_map *map);
void				destroy_map(t_map *map);

/*==== move_vector.c ====*/

void				accumulate_vector(t_map *map, double *v_x, double *v_y);
void				normalize_vector(double *v_x, double *v_y);
void				calc_move_vector(t_map *map, double *v_x, double *v_y);

/*==== move.c ====*/

void				get_bounding_cells(double px, double py, t_bounds *bounds);
int					is_cell_walkable(t_map *map, int x, int y);
int					is_walkable(t_map *map, double px, double py);
void				apply_move(t_map *map, double v_x, double v_y);
void				apply_rotation(t_map *map);

/*==== rotation.c ====*/

void				rotate_left(t_map *map);
void				rotate_right(t_map *map);

/*==== window_management.c ====*/

int					init_window(t_game *game);
void				destroy_mlx(t_game *game);

/* INIT */

/*==== init_directions.c ====*/

void				init_dir_north(t_map *map);
void				init_dir_south(t_map *map);
void				init_dir_east(t_map *map);
void				init_dir_west(t_map *map);
int					init_player_dir(t_map *map);

/*==== init_structs.c ====*/

int					init_textures(t_textures *textures);
int					init_texpath(t_texpath *texpath);
int					init_game_struct(t_game *game);
int					init_struct(t_map *map);

/* PARSING */

/*==== char_validation.c ====*/

int					parse_char(char c);

/*==== map_utils.c ====*/

int					process_map_line(char *line, char **temp_map, int *height,
						int *max_width);
int					copy_map_row(t_map *map, char **temp_map, int i);
int					finalize_map(t_map *map, char **temp_map);
int					is_out_of_bounds(int x, int y, int width, int height);
int					is_touching_void(t_map *map, int x, int y);

/*==== map_validation.c ====*/

int					validate_map(t_map *map);
int					check_invalid_char(t_map *map);
int					check_single_player(t_map *map);
int					find_player_position(t_map *map);
int					validate_void_surroundings(t_map *map);

/*==== parse_map.c ====*/

int					parse_map(t_map *map, char *file_path);
int					open_map_file(char *file_path);
int					read_map_lines(int fd, t_map *map);
char				**allocate_temp_map(void);
int					fill_temp_map(int fd, char **temp_map, int *height,
						int *max_width);

/*==== print.c ====*/

void				print_map(t_map *map);

/*==== player_init.c ====*/

int					set_player_position(t_map *map, int x, int y);
void				fill_voids_with_walls(t_map *map);

/* RAYCASTING */

/*==== minimap.c ====*/

void				draw_player(t_rect rect, t_game *game);
void				draw_minimap_player(t_map *map, int offset_x, int offset_y);
void				draw_minimap_cells(t_map *map, int offset_x, int offset_y);
void				draw_minimap(t_map *map);

/*==== raycasting.c ====*/

void				calc_camera_ray(double *ray_x, double *ray_y, t_map *map,
						int i);
void				set_ray_data(t_map *map, t_ray *ray, double ray_x,
						double ray_y);
void				init_dda(t_map *map, t_ray *ray);
int					perform_dda(t_map *map, t_ray *ray);
void				calc_perp_dist(t_map *map, t_ray *ray);

/*==== raycaster.c ====*/

void				render_walls(t_map *map);

/*==== render_walls.c ====*/

void				put_pixel(int x, int y, int color, t_game *game);
void				draw_wall_column(t_game *game, int i, t_ray *ray);
void				draw_line(t_map *map, double ray_x, double ray_y, int i);

/*==== ray_init.c ====*/

void				compute_camera_ray(t_map *map, t_ray *ray, int x);
void				compute_delta_distances(t_ray *ray);
void				compute_step_and_side(t_map *map, t_ray *ray);
void				init_ray(t_map *map, t_ray *ray, int x);

/*==== ray_projection.c ====*/

void				calc_projection(t_map *map, t_ray *ray);
int					compute_texx(t_map *map, t_ray *ray);

/*==== ray_texture.c ====*/

int					select_texture(t_ray *ray);
void				draw_textures(t_map *map, t_ray *ray, int x, int texx);
void				draw_column(t_map *map, t_ray *ray, int x);

/* TEXTURES */

/*==== load_textures.c*/

int					load_textures(t_map *map);

/*==== parse_textures.c ====*/

int					parse_textures_colors(t_texpath *texpath, char *file_path);
int					parse_line(t_texpath *texpath, char *line);
int					handle_texture_line(t_texpath *texpath, char *line);
int					handle_color_line(t_texpath *texpath, char *line);

/*==== rgb_utils.c ====*/

int					convert_rgb(unsigned int r, unsigned int g, unsigned int b);
int					parse_rgb(const char *str, int *res);
int					check_exist_textures(t_texpath *texpath);
int					check_xpm_file(const char *file_path);

/*==== texture_utils.c ====*/

int					handle_ceiling(t_texpath *texpath, char *line);
int					handle_floor(t_texpath *texpath, char *line);
int					destroy_texpath(t_texpath *texpath);
int					check_textures(t_texpath *texpath);

#endif