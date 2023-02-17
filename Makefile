# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fholwerd <fholwerd@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/11/08 15:59:07 by fholwerd      #+#    #+#                  #
#    Updated: 2023/02/17 14:18:17 by fholwerd      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

ROOT	= $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
NAME	= minishell
SRC		= $(ROOT)src/main.c \
			$(ROOT)src/info.c \
			$(ROOT)src/env/copy_env.c \
			$(ROOT)src/env/env_add.c \
			$(ROOT)src/env/env_pop.c \
			$(ROOT)src/executer/builtins.c \
			$(ROOT)src/executer/errors.c \
			$(ROOT)src/executer/executer.c \
			$(ROOT)src/executer/ft_split.c \
			$(ROOT)src/executer/pathfind.c \
			$(ROOT)src/executer/utils.c \
			$(ROOT)src/lexer/cmds_struct_tools.c \
			$(ROOT)src/lexer/expand.c \
			$(ROOT)src/lexer/file_struct_tools.c \
			$(ROOT)src/lexer/separate_cmds.c \
			$(ROOT)src/lexer/split_commands.c \
			$(ROOT)src/lexer/split_utils.c \
			$(ROOT)src/lexer/trim_cmds.c \
			$(ROOT)src/utils/array_len.c \
			$(ROOT)src/utils/free_split.c \
			$(ROOT)src/utils/ft_is_al_under.c \
			$(ROOT)src/utils/ft_putendl_fd.c \
			$(ROOT)src/utils/ft_putstr_fd.c \
			$(ROOT)src/utils/ft_split.c \
			$(ROOT)src/utils/ft_strdup.c \
			$(ROOT)src/utils/ft_strjoin.c \
			$(ROOT)src/utils/ft_strlen.c \
			$(ROOT)src/utils/ft_strncmp.c \
			$(ROOT)src/utils/ft_strndup.c \
			$(ROOT)src/utils/ft_substr.c \
			$(ROOT)src/utils/printer.c \
			$(ROOT)src/utils/stop.c
OBJ		= $(SRC:.c=.o)
INCLUDE	= -I $(ROOT)include \
			-I $(ROOT)include/env \
			-I $(ROOT)include/executer \
			-I $(ROOT)include/lexer \
			-I $(ROOT)include/utils \
			-I /Users/fholwerd/.brew/opt/readline/include
LINKS	= -L /Users/fholwerd/.brew/opt/readline/lib -lreadline
CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

$(NAME): $(OBJ)
	@echo "Compiling executable."
	@$(CC) $(CFLAGS) $(OBJ) $(LINKS) -o $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all libs clean fclean re