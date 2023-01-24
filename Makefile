# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bpoumeau <bpoumeau@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 03:31:03 by bpoumeau          #+#    #+#              #
#    Updated: 2023/01/24 03:10:01 by bpoumeau         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME := pipex

CC := cc
FLAGS := -Wall -Wextra -Werror -Iincludes -Ilibft

HEADER := includes/pipex.h

HLIB :=	libft/libft.h \

FILES := close_pipes.c \
	create_tool.c \
	exec_cmd.c \
	init_commands.c \
	init_pipes.c \
	main.c \
	parse_path.c \
	perr_utils.c \
	wait.c

SRC := $(addprefix srcs/, $(FILES))

OBJ := $(addprefix obj/, $(FILES:.c=.o))

LIBS = libft/libft.a
LIB_FLAGS := -Llibft -lft

all:
	make -C libft
	$(MAKE) $(NAME)

$(NAME): $(LIBS) $(OBJ)
	$(CC) $(FLAGS) $(LIB_FLAGS) $(OBJ) -o $(NAME) $(LIBS)

obj/%.o: srcs/%.c $(HEADER) $(HLIB)
	mkdir -p ${shell dirname $@}
	$(CC) $(FLAGS) -c $< -o $@

$(ODIR):
	mkdir $(ODIR)

clean:
	rm -rf obj/

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

normy:
	norminette $(SRC) $(HEADER)

.PHONY: all clean fclean re libclean normy

