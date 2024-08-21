# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/21 12:23:07 by csturm            #+#    #+#              #
#    Updated: 2024/08/21 17:46:02 by marianfurni      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project Name and Compiler Settings
NAME := miniRT
COMPILER := cc
FLAGS := -Wall -Wextra -Werror -g
CLEANUP := rm -rf
# MLX_LIBS := -L minilibx-linux -lmlx -lm -lXext -lX11

# Directory Paths
OBJECTS_PATH := obj/
SOURCES_PATH := src/
LIBFT_PATH := libft/
INCLUDES := -I inc -I $(LIBFT_PATH)

# Source and Object Files
SOURCE_FILES := main.c \
                Parser/parse.c Parser/parse_camera.c Parser/parse_spheres.c Parser/parse_planes.c Parser/light_utils.c Parser/cylinder_utils.c\
				Parser/parse_light.c error.c Parser/parse_ambient.c Parser/parse_cylinders.c Parser/utils.c Parser/plane_utils.c \

OBJECTS := $(SOURCE_FILES:%.c=$(OBJECTS_PATH)%.o)
LIBFT := $(LIBFT_PATH)libft.a

# Build the Project
all: $(NAME)

# Linking the Program
$(NAME): $(LIBFT) $(OBJECTS)
	@$(COMPILER) $(FLAGS) $(OBJECTS) -L$(LIBFT_PATH) -lft $(MLX_LIBS) -o $(NAME)
	@echo "linking successful - executable $(NAME) created"

# Compiling Source Files
$(OBJECTS_PATH)%.o: $(SOURCES_PATH)%.c
	@mkdir -p $(@D)
	@$(COMPILER) $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo "$< compiled successfully"

# Compiling libft
$(LIBFT):
	@echo "Compiling libft"
	@$(MAKE) -s -C $(LIBFT_PATH)

# Cleaning Up Object Files
clean:
	@$(CLEANUP) $(OBJECTS)
	@$(CLEANUP) $(OBJECTS_PATH)
	@$(MAKE) -s -C $(LIBFT_PATH) clean
	@echo "object cleanup completed"

# Full Clean-Up
fclean: clean
	@$(CLEANUP) $(NAME)
	@$(MAKE) -s -C $(LIBFT_PATH) fclean
	@echo "cleanup completed"

# Recompile the Projects
re: fclean all
	@echo "recompilation completed"

# Phony Targets
.PHONY: all clean fclean re
