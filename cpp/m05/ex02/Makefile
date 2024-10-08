NAME		= ex02
CXX			= g++
RM			= rm -f
CPPFLAGS 	= -Wall -Wextra -Werror -std=c++98 -pedantic 
OBJ			= $(SRC:.cpp=.o)
SRC 		= main.cpp \
			  Bureaucrat.cpp \
			  Form.cpp \
			  PresidentialPardonForm.cpp \
			  RobotomyRequestForm.cpp \
			  ShrubberyCreationForm.cpp \

HEADER		= Bureaucrat.hpp \
			  Form.hpp \
			  PresidentialPardonForm.hpp \
			  RobotomyRequestForm.hpp \
			  ShrubberyCreationForm.hpp \

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