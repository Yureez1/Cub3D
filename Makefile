# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/04 17:01:27 by jbanchon          #+#    #+#              #
#    Updated: 2025/06/04 17:01:44 by jbanchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cub3d
CFLAGS = -Wall -Wextra -Werror -g -Imlx
OBJS = $(SRCS:.c=.o)

SRCS = main.c \

MLX_DIR = ./mlx
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

LILA = \033[1;38;5;206m
GREEN = \033[32m
NC = \033[0m

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

all: $(NAME)
	@echo "$(LILA)Compiling Cub3D...$(NC)"
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)Cub3D compiled successfully!$(NC)"

clean:
	@echo "$(LILA)Cleaning up object files...$(NC)"
	rm -f $(OBJS)
	rm -f $(NAME)
	@echo "$(GREEN)Object files cleaned!$(NC)"

fclean: clean
	@echo "$(LILA)Cleaning up all files...$(NC)"
	rm -f $(NAME)
	@echo "$(GREEN)All files cleaned!$(NC)"

re: fclean all

.PHONY: fclean all