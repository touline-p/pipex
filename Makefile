# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bpoumeau <bpoumeau@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 03:31:03 by bpoumeau          #+#    #+#              #
#    Updated: 2023/01/11 15:35:40 by bpoumeau         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME := pipex

CC := cc
FLAGS :=   -Wall -Wextra -Werror -Iincludes

HEADER := includes/pipex.h

FILE := main.c \
	create_tool.c \
	exec_cmd.c \
	init_commands.c \
	init_pipes.c \
	parse_path.c \
	perr_utils.c \
	close_pipes.c \
	wait.c

SRCS := $(addprefix srcs/, $(FILE))
OBJ := $(addprefix obj/, $(FILE:.c=.o))

LIBS := includes/libft.a \
	includes/libft.h

all: $(NAME)

$(NAME): $(LIBS) $(OBJ) 
	$(CC) $(FLAGS) -Lincludes -lft -Iincludes $(OBJ) -o $(NAME) 

obj/%.o: srcs/%.c $(HEADER) 
	$(CC) $(FLAGS) -c $< -o $@ -I includes

$(LIBS): 
	make re -C libft
	cp libft/libft.h includes/
	cp libft/libft.a includes/
	
clean:
	make fclean -C libft
	rm includes/libft.h
	rm includes/libft.a
	rm $(OBJ)

fclean: clean 
	rm -f $(NAME)

re: fclean all

normy:
	norminette $(SRCS) $(HEADER)

test: $(NAME)
	./pipex Makefile cat you

test1: $(NAME)
	./pipex Makefile cat cat you

test2: $(NAME)
	./pipex Makefile cat cat cat you

.PHONY: all clean fclean re libclean normy
