# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 23:33:38 by root              #+#    #+#              #
#    Updated: 2022/05/18 02:29:02 by dantremb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

# Fichiers sources.
SRCS_FILES = pipex.c get_cmd_path.c
LIBFT = includes/libft/libft.a
LIBFT_PATH = includes/libft/
SRCS_PATH = srcs/
SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILES))

# Compilateurs
AR = ar
CC = gcc

# Flags
ARFLAGS = rcs
CFLAGS = -Wall -Wextra -Werror -g

# Macros
REMOVE = rm -rf
COMMIT = $(shell date "+%d %B %T")

# Transforme les fichiers .c en fichiers .o
# La premiere utilise le contenu de la 2e pour compiler.
# J'imprime un tiret (sans newline) pour créer ma ligne de progression.
OBJS= $(SRCS:%.c=%.o)
%.o: %.c
	@printf "-"
	@$(CC) $(CFLAGS) -o $@ -c $<

# On appel la commande INIT et NAME puis on imprime le message final.
all: init $(NAME)
	@echo "> Done!."
	@echo "$(NAME) Compiled!"

# On Appel le fichier Make de la librairie Libft et on imprime
# le début de la compilation de pipex à l'écran (sans newline).
init:
	@echo "Preparing Libft"
	@$(MAKE) -s -C $(LIBFT_PATH)
	@echo "Preparing Pipex"
	@printf "Compiling -"

# On appel la création des OBJS et ensuite on compile le programme.
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

# Commande de nettoyage.
clean:
	@$(REMOVE) $(OBJS)
	@@$(MAKE) -s clean -C $(LIBFT_PATH)
fclean: clean
	@$(REMOVE) $(NAME)
	@$(MAKE) -s fclean -C $(LIBFT_PATH)

# On nettoie et recompile.
re:	fclean all

# On peut choisir le nom de commit avec "make git COMMIT="
git:
	@git add .
	@git commit -m "$(COMMIT)"
	@git push