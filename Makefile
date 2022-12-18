NAME	=	pipex

CC		=	cc

CFLAGS	=	-Werror -Wall -Wextra #-L$(DDIR) -lft

AR		= 	ar

ARFLAGS =	rcs

SANITY	=	-g -fsanitize=address

FILES	=	main.c \
create_tool.c \
init_pipes.c \
perr_utils.c \
init_commands.c \

SDIR	=	srcs/
SRCS	=	$(addprefix $(SDIR), $(FILES))

HDIR	=	includes/
HEADER	=	pipex.h \
		libft.h
HEADERS =	$(addprefix $(HDIR), $(HEADER))

ODIR	=	obj/
OBJS	=	$(addprefix $(ODIR), $(FILES:.c=.o))

LIBS	=	libft.a
LNAME	=	$($(LIBS:lib=-l):.a=)
DDIR	=	dependancies/
DPPS	=	$(addprefix $(DDIR), $(LIBS))

all	:	$(NAME)

$(NAME)	:	$(OBJS) $(DPPS) $(HEADERS) 
	$(CC) $(CFLAGS) -o $(NAME)  $(OBJS) -lft -L$(DDIR)

obj/%.o	:	srcs/%.c $(ODIR) $(DPPS) $(HEADERS) 
	$(CC) $(CFLAGS) -I $(HDIR) -o $@ -c $< 

$(DDIR)	:
	mkdir $(DDIR)
	
$(ODIR)	:
	mkdir $(ODIR)

$(DPPS)	:	$(DDIR)
	make -C libft
	mv libft/libft.a $(DPPS)
	cp libft/libft.h includes/libft.h

clean	:
	-rm -rf $(OBJS)
	make -C libft clean
	-rm $(DPPS)

fclean	:	clean
	-rm $(NAME)
	make -C libft fclean

re	:	fclean all

update	:
	cp ~/lib/$(HEADER) $(HDIR)

.PHONY	:	all clean fclean re ncpy test update
