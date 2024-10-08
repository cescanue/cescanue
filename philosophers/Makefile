NAME		= philo
NAMEB		= philo_bonus
INCLUDE		= includes
INCLUDEB	= includes_bonus
SRC_DIR		= srcs/philo/
SRC_DIRB	= srcs/philo_bonus/
OBJ_DIR		= obj/
CC			= cc
CFLAGS		= -Werror -Wall -Wextra -I
RM			= rm -f
SRC_FILES	= philosophers \
			  philosophers_init \
			  philosophers_utils \
			  philosophers_error \
			  philosophers_time \
			  philosophers_philo \
			  philosophers_philo_eat \
			  
SRC_FILESB	= philosophers_bonus \
			  philosophers_init_bonus \
			  philosophers_utils_bonus \
			  philosophers_error_bonus \
			  philosophers_time_bonus \
			  philosophers_philo_bonus \
			  philosophers_philo_eat_bonus \
		  
HEADER		=	includes/philosophers.h \

HEADERB		=	includes_bonus/philosophers_bonus.h \

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
OBJB 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILESB)))

OBJF		=	.cache_exists

all:		$(NAME)

$(NAME):	$(OBJ) 
			@$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) -o $(NAME)
			@echo "philosophers compiled!"
			
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) | $(OBJF)
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIRB)%.c $(HEADERB) | $(OBJF)
			@$(CC) $(CFLAGS) $(INCLUDEB) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

bonus:		$(NAMEB)

$(NAMEB):	$(OBJB)
			@$(CC) $(CFLAGS) $(INCLUDEB) $(OBJB) -o $(NAMEB)
			@echo "philosophers_bonus compiled!"

clean:
			@$(RM) -rf $(OBJ_DIR)
			
fclean:		clean
			@$(RM) -f $(NAME)
			@$(RM) -f $(NAMEB)		
			
re:			fclean all

.PHONY:		all clean fclean re