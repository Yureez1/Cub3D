# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/04 17:01:27 by jbanchon          #+#    #+#              #
#    Updated: 2025/07/17 17:13:47 by leaugust         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -g -Werror -I$(MLX_DIR) -I$(GNL_DIR) -I$(LIBFT_DIR)
CFLAGS_NORMAL = $(CFLAGS) -I./srcs/inc
CFLAGS_BONUS = $(CFLAGS) -I./bonus/inc -DBONUS
LDFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd -L$(LIBFT_DIR) -lft

GNL_DIR = ./gnl
MLX_DIR = ./minilibx-linux
LIBFT_DIR = ./libft
LIBFT_A = $(LIBFT_DIR)/libft.a
MLX_A = $(MLX_DIR)/libmlx.a

OBJ_DIR = objs
BONUS_OBJ_DIR = objs_bonus

SRCS = \
	srcs/main.c srcs/parsing/map_utils.c srcs/parsing/map_validation.c srcs/parsing/parse_map.c\
	srcs/parsing/player_init.c srcs/parsing/void_check.c srcs/parsing/line_check.c srcs/textures/parse_textures.c\
	srcs/textures/rgb_utils.c srcs/textures/parse_utils.c srcs/textures/texture_utils.c srcs/raycasting/raycasting.c\
	srcs/raycasting/raycaster.c srcs/raycasting/render_walls.c srcs/raycasting/ray_texture.c srcs/raycasting/ray_projection.c\
	srcs/raycasting/ray_init.c srcs/init/init_structs.c srcs/init/init_directions.c\
	srcs/game/game_loop.c srcs/game/input_handling.c srcs/game/map_management.c\
	srcs/game/move.c srcs/game/rotation.c srcs/game/window_management.c srcs/game_textures/load_textures.c\
	$(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c $(GNL_DIR)/gnl.c \

BONUS_SRCS = \
	bonus/main.c bonus/parsing/map_utils.c bonus/parsing/map_validation.c\
	bonus/parsing/parse_map.c bonus/parsing/player_init.c bonus/parsing/void_check.c bonus/parsing/line_check.c\
	bonus/textures/parse_textures.c bonus/textures/rgb_utils.c bonus/textures/texture_utils.c bonus/textures/parse_utils.c bonus/raycasting/raycasting.c\
	bonus/raycasting/raycaster.c bonus/raycasting/render_walls.c bonus/raycasting/ray_texture.c bonus/raycasting/ray_projection.c\
	bonus/raycasting/ray_init.c bonus/init/init_structs.c bonus/init/init_directions.c bonus/game/game_loop_bonus.c\
	bonus/game/input_handling.c bonus/game/map_management.c bonus/game/move_vector.c bonus/game/rotation.c\
	bonus/game/window_management.c bonus/game_textures/load_textures.c bonus/game/collision_bonus.c bonus/game/move_bonus.c\
	bonus/raycasting/minimap_bonus.c $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c $(GNL_DIR)/gnl.c\

OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))
BONUS_OBJS = $(patsubst %.c, $(BONUS_OBJ_DIR)/%.o, $(BONUS_SRCS))

LILA = \033[1;38;5;206m
GREEN = \033[32m
NC = \033[0m

all: libft mlx $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) $(MLX_A) $(OBJ_DIR)/.normal_flag

bonus: libft mlx $(BONUS_OBJ_DIR)/.bonus_flag

$(OBJ_DIR)/.normal_flag: $(OBJS) $(LIBFT_A) $(MLX_A)
	@rm -f $(BONUS_OBJ_DIR)/.bonus_flag
	@mkdir -p $(OBJ_DIR)
	@echo "$(LILA)Compiling Cub3D (normal)...$(NC)"
	@$(CC) $(CFLAGS_NORMAL) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)Cub3D compiled successfully!$(NC)"
	@touch $@

$(BONUS_OBJ_DIR)/.bonus_flag: $(BONUS_OBJS) $(LIBFT_A) $(MLX_A)
	@rm -f $(OBJ_DIR)/.normal_flag $(NAME)
	@rm -rf $(OBJ_DIR)
	@mkdir -p $(BONUS_OBJ_DIR)
	@echo "$(LILA)Compiling Cub3D (bonus)...$(NC)"
	@$(CC) $(CFLAGS_BONUS) $(BONUS_OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)Cub3D bonus compiled successfully!$(NC)"
	@touch $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS_NORMAL) -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS_BONUS) -c $< -o $@

$(LIBFT_A):
	@echo "$(LILA)Compiling libft...$(NC)"
	@$(MAKE) -s -C $(LIBFT_DIR)
	@echo "$(GREEN)libft compiled successfully!$(NC)"

mlx: $(MLX_A)

$(MLX_A):
	@echo "$(LILA)Compiling MiniLibX...$(NC)"
	@$(MAKE) -s -C $(MLX_DIR)
	@echo "$(GREEN)MiniLibX compiled successfully!$(NC)"

clean:
	@echo "$(LILA)Cleaning up object files...$(NC)"
	@rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)
	@rm -f $(OBJ_DIR)/.normal_flag $(BONUS_OBJ_DIR)/.bonus_flag
	@$(MAKE) -s -C $(LIBFT_DIR) clean > /dev/null
	@$(MAKE) -s -C $(MLX_DIR) clean > /dev/null || true
	@echo "$(GREEN)Object files cleaned!$(NC)"

fclean: clean
	@echo "$(LILA)Cleaning up all files...$(NC)"
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean > /dev/null
	@$(MAKE) -s -C $(MLX_DIR) clean > /dev/null || true
	@echo "$(GREEN)All files cleaned!$(NC)"

re: fclean all

.PHONY: fclean all libft clean bonus re mlx