NAME		= ex03
CXX			= g++
RM			= rm -f
CPPFLAGS 	= -Wall -Wextra -Werror -std=c++98 -pedantic #-g -fsanitize=address
OBJ			= $(SRC:.cpp=.o)
SRC 		= main.cpp \
			  AMateria.cpp \
			  Character.cpp \
			  Cure.cpp \
			  Ice.cpp \
			  MateriaSource.cpp \

HEADER		= AMateria.hpp \
			  Character.hpp \
			  Cure.hpp \
			  ICharacter.hpp \
			  IMateriaSource.hpp \
			  Ice.hpp \
			  MateriaSource.hpp \



all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)
	@echo $(NAME) "compiled"

%.o: %.cpp ${HEADER}
	@$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re