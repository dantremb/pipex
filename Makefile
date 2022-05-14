# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 23:33:38 by root              #+#    #+#              #
#    Updated: 2022/05/14 16:13:20 by dantremb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

PRINT_NAME = Pipex

SRCS_FILES = pipex.c

SRCS_PATH = srcs/

LIBFT = libft/libft.a

OBJS= $(SRCS:%.c=%.o)

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILES))

AR = ar

ARFLAGS = rcs

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

REMOVE = rm -rf

COMMIT = $(shell date "+%d %B %T")

all: init $(NAME)
	@echo "> Done!."
	@echo "$(PRINT_NAME) Compiled!"
	
init:
	@echo "Preparing Libft"
	@$(MAKE) -s -C libft/
	@echo "Preparing Pipex"
	@printf "Compiling -"

%.o: %.c
	@printf "-"
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

clean:
	@$(REMOVE) $(OBJS)
	@@$(MAKE) -s clean -C libft/

fclean: clean
	@$(REMOVE) $(NAME)
	@$(MAKE) -s fclean -C libft/

re:	fclean all

git:
	@git add .
	@git commit -m "$(COMMIT)"
	@git push