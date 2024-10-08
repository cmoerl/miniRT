# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/15 10:09:21 by csturm            #+#    #+#              #
#    Updated: 2024/08/04 23:33:47 by marianfurni      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC := cc
CFLAGS := -Wall -Wextra -Werror -g
NAME := libft.a
CLEANUP := rm -rf

# Directories
SRCS_DIR := ./
OBJS_DIR := objs/

# List of source and object files
SRCS := ft_atoi.c ft_isalpha.c ft_memchr.c ft_memset.c ft_strlcat.c ft_strnstr.c ft_tolower.c \
ft_bzero.c ft_isascii.c ft_memcmp.c ft_strchr.c ft_strlcpy.c ft_strrchr.c ft_toupper.c \
ft_calloc.c ft_isdigit.c ft_memcpy.c ft_strdup.c ft_strlen.c ft_strtrim.c ft_itoa.c \
ft_isalnum.c ft_isprint.c ft_memmove.c ft_strjoin.c ft_strncmp.c ft_substr.c ft_split.c \
ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_atoi_base.c \
ft_itoa_base.c ft_putnbr_base_fd.c ft_putnbr_unsigned_fd.c ft_uitoa.c ft_printf.c handle_char.c handle_hex_lower.c \
handle_hex_upper.c handle_int.c handle_percent.c handle_pointer.c handle_specifier.c handle_string.c handle_uint.c ft_isnum.c \
ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_printlist.c ft_atoi_long.c ft_atoi_overflow.c ft_strok.c \
ft_strcat.c ft_strcpy.c ft_strcmp.c ft_strcspn.c ft_isspace.c ft_strnlen.c ft_strndup.c get_next_line.c ft_atof.c


OBJS := $(SRCS:%.c=$(OBJS_DIR)%.o)

# Default rule to make libft.a
all: $(NAME)

# Creating the Library
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	@echo "library $(NAME) created"

# Compiling every source file into its object file
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$< compiled successfully"

# Clean rule to remove object files
clean:
	@$(CLEANUP) $(OBJS)
	@$(CLEANUP) $(OBJS_DIR)

# Fclean rule to remove both object files and libft.a
fclean: clean
	@$(CLEANUP) $(NAME)

# Rule to recompile everything
re: fclean all

.PHONY: all clean fclean re
