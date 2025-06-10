# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/04 17:01:27 by jbanchon          #+#    #+#              #
#    Updated: 2025/06/10 14:55:36 by leaugust         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(MLX_DIR) -I$(GNL_DIR)
LDFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

GNL_DIR = ./gnl
MLX_DIR = ./mlx

OBJ_DIR = objs

SRCS = \
	srcs/main.c \
	srcs/parsing/parse_map.c \
	srcs/parsing/player_pos.c \
	srcs/parsing/map_enclosure.c \
	$(GNL_DIR)/get_next_line.c \
	$(GNL_DIR)/get_next_line_utils.c \

OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

LILA = \033[1;38;5;206m
GREEN = \033[32m
NC = \033[0m


all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(LILA)Compiling Cub3D...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)Cub3D compiled successfully!$(NC)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	@echo "$(LILA)Cleaning up object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@rm -f $(OBJS)
	@echo "$(GREEN)Object files cleaned!$(NC)"

fclean: clean
	@echo "$(LILA)Cleaning up all files...$(NC)"
	@rm -f $(NAME)
	@echo "$(GREEN)All files cleaned!$(NC)"

re: fclean all

.PHONY: fclean all