NAME		= push_swap
NAME_B		= checker
INCLUDE		= includes
SRC_DIR		= srcs/
OBJ_DIR		= obj/
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I
RM			= rm -f
SRC_FILES_B	= bonus/checker_bonus \
			  bonus/get_next_line_bonus \
			  bonus/get_next_line_utils_bonus \
			  push_swap_prg \
			  push_swap_std_funtions \
			  push_swap_std2_funtions \
			  push_swap_std3_funtions \
			  push_swap_lst_funtions \
			  push_swap_lst2_funtions \
			  push_swap_instructions \
			  push_swap_instructions1 \
			  push_swap_instructions2 \
			  push_swap_radix \

SRC_FILES	= push_swap \
			  push_swap_prg \
			  push_swap_std_funtions \
			  push_swap_std2_funtions \
			  push_swap_std3_funtions \
			  push_swap_lst_funtions \
			  push_swap_lst2_funtions \
			  push_swap_instructions \
			  push_swap_instructions1 \
			  push_swap_instructions2 \
			  push_swap_radix \
			  push_swap_morder \
			  push_swap_morder1 \
			  push_swap_morder2 \
			  push_swap_morder3 \
			  push_swap_interactive \
			  			  
HEADER		=	includes/push_swap.h \

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

SRCB 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES_B)))
OBJB 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES_B)))

OBJF		=	.cache_exists

all:		$(NAME) 

$(NAME):	$(OBJ)
			@$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) -o $(NAME)
			@echo push_swap compiled!!

$(NAME_B):	$(OBJB)
			@$(CC) $(CFLAGS) $(INCLUDE) $(OBJB) -o $(NAME_B)
			@echo checker compiled!!

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) | $(OBJF)
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)
			@mkdir -p $(OBJ_DIR)/bonus
			
bonus:		$(NAME_B)

clean:
			@$(RM) -rf $(OBJ_DIR)

fclean:		clean
			@$(RM) -f $(NAME)
			@$(RM) -f checker
			
re:			fclean all

.PHONY:		all clean fclean re