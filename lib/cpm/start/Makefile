SRC		=		src/$name.c		\
				main.c

INC		=		-Iinclude

CFLAGS	+=		$(INC) -W -Werror -Wall -Wextra

OBJ		=		$(SRC:.c=.o)

NAME	=		$name

all:	$(OBJ)
		gcc -o $(NAME) $(OBJ)

clean:
		rm -rdf $(OBJ)

fclean:	clean
		rm -rdf $(NAME)

re:		fclean all

.PHONY:	all clean fclean re
