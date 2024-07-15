# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csturm <csturm@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/21 12:23:07 by csturm            #+#    #+#              #
#    Updated: 2024/07/15 09:28:02 by csturm           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# how to link the minilibX?
# also link libft --> including get_next_line!

# Project Name and Compiler Settings
NAME := miniRT
COMPILER := cc
FLAGS := -Wall -Wextra -Werror -g
CLEANUP := rm -rf
MLX_LIBS := -L minilibx-linux -lmlx -lm -lXext -lX11

# Directory Paths
OBJECTS_PATH := obj/
SOURCES_PATH := src/

# Source and Object Files

SOURCE_FILES := main.c \
				render.c \
				error.c \
				events.c \
				graphics.c \
				intersect.c \
				ray.c \
				ray_utils.c \
				#parse.c \

OBJECTS := $(SOURCE_FILES:%.c=$(OBJECTS_PATH)%.o)

# Build the Project
all: $(NAME)

# Linking the Program
$(NAME): $(OBJECTS)
	@$(COMPILER) $(FLAGS) $(OBJECTS) $(MLX_LIBS) -o $(NAME)
	@echo "linking successfull - executable $(NAME) created"

# Compiling Source Files
$(OBJECTS_PATH)%.o: $(SOURCES_PATH)%.c
	@mkdir -p $(@D)
	@$(COMPILER) $(FLAGS) -c $< -o $@
	@echo "$< compiled successfully"

# Cleaning Up Object Files
clean:
	@$(CLEANUP) $(OBJECTS)
	@$(CLEANUP) $(OBJECTS_PATH)
	@echo "object cleanup completed"

# Full Clean-Up
fclean: clean
	@$(CLEANUP) $(NAME)
	@echo "$(NAME) cleanup completed"

# Recompile the Projects
re: fclean all
	@echo "recompilation completed"

# Phony Targets
.PHONY: all clean fclean re