# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 23:33:38 by root              #+#    #+#              #
#    Updated: 2022/05/14 10:03:48 by dantremb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

PRINT_NAME = Pipex

SRCS_FILES = pipex.c

SRCS_PATH = srcs/

OBJS= $(SRCS:%.c=%.o)

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILES))

AR = ar

ARFLAGS = rcs

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

REMOVE = rm -rf

COMMIT = $(shell date "+%d %B %T")

all: init $(NAME)
	echo "> Done!.\n"
	echo "$(PRINT_NAME) Compiled!"
	
init:
	echo "Compiling Libft"
	make -C libft/
	echo "Compiling Pipex"

%.o: %.c
	printf "-"
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(REMOVE) $(OBJS)
	make clean -C libft/

fclean: clean
	$(REMOVE) $(NAME)
	make fclean -C libft/

re:	fclean all

git:
	git add .
	git commit -m "$(COMMIT)"
	git push