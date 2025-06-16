# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbanchon <jbanchon@student42.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/04 17:01:27 by jbanchon          #+#    #+#              #
#    Updated: 2025/06/16 13:57:05 by jbanchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(MLX_DIR) -I$(GNL_DIR) -I$(LIBFT_DIR)
LDFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd -L$(LIBFT_DIR) -lft

GNL_DIR = ./gnl
MLX_DIR = ./mlx
LIBFT_DIR = ./libft

OBJ_DIR = objs

SRCS = \
	srcs/main.c \
	srcs/parsing/map_loader.c \
	srcs/parsing/map_parser.c \
	srcs/parsing/map_checker.c \
	srcs/parsing/player_pos.c \
	srcs/parsing/print_map.c \
	srcs/parsing/parse_char.c \
	srcs/parsing/map_textures.c \
	$(GNL_DIR)/get_next_line.c \
	$(GNL_DIR)/get_next_line_utils.c \

OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

LILA = \033[1;38;5;206m
GREEN = \033[32m
NC = \033[0m

all: libft $(NAME)

$(NAME): $(OBJS)
	@echo "$(LILA)Compiling Cub3D...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)Cub3D compiled successfully!$(NC)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

libft:
	@echo "$(LILA)Compiling libft...$(NC)"
	@$(MAKE) -s -C $(LIBFT_DIR) > /dev/null
	@echo "$(GREEN)libft compiled successfully!$(NC)"
	
clean:
	@echo "$(LILA)Cleaning up object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean > /dev/null
	@echo "$(GREEN)Object files cleaned!$(NC)"

fclean: clean
	@echo "$(LILA)Cleaning up all files...$(NC)"
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean > /dev/null
	@echo "$(GREEN)All files cleaned!$(NC)"

re: fclean all

.PHONY: fclean all libft clean