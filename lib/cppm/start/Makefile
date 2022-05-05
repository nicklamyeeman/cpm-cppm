SRC		=		src/$Name.cpp		\
				main.cpp

INC		=		-Iinclude

CPPFLAGS+=		$(INC) -W -Werror -Wall -Wextra

OBJ		=		$(SRC:.cpp=.o)

NAME	=		$name

all:	$(OBJ)
		g++ -o $(NAME) $(OBJ)

clean:
		rm -rdf $(OBJ)

fclean:	clean
		rm -rdf $(NAME)

re:		fclean all

.PHONY:	all clean fclean re
