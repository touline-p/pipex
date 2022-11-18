NAME	=	pipex

CC		=	cc

CFLAGS	=	-Werror -Wall -Wextra

AR		= 	ar

ARFLAGS =	rcs

SANITY	=	-g -fsanitize=address

FILES	=	 
SDIR	=	src/
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

$(NAME)	:	$(OBJS) $(DPPS) $(HEADERS) Makefile 
	$(CC) $(CFLAGS) $(NAME) -o $(OBJS) -L$(DDIR) 

obj/%.o	:	src/%.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -I $(HDIR) -o $@ -c $<

$(DDPS)	:
	cd	$(DDIR)
	make $(LIBS)
	cd ..

clean	:
	rm -rf $(OBJS)

fclean	:	clean
	rm $(NAME)

re	:	fclean all

update	:
	cp ~/lib/$(HEADER) $(HDIR)

.PHONY	:	all clean fclean re ncpy test update
