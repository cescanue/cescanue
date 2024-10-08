NAME		= pipex
NAMEB		= pipex_bonus
INCLUDE		= includes
INCLUDEB	= includes_bonus
SRC_DIR		= srcs/pipex/
SRC_DIRB	= srcs/pipex_bonus/
OBJ_DIR		= obj/
CC			= cc
CFLAGS		= -Werror -Wall -Wextra -I
RM			= rm -f
LIB			= ftprintf
LIBFT		= ft_printf/libft
FT_PRINTF	= ft_printf

SRC_FILES	= pipex \
			  pipex_exec \
			  			  
SRC_FILESB	= pipex_bonus \

HEADER		=	includes/pipex.h \

HEADERB		=	includes_bonus/pipex_bonus.h \

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
OBJB 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILESB)))

OBJF		=	.cache_exists

all:		$(NAME)

make_libs:
			@make -C $(FT_PRINTF)

$(NAME):	make_libs $(OBJ)
			@$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) -Lft_printf -l$(LIB) -o $(NAME)
			@echo "pipex compiled!"
			
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) | $(OBJF)
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIRB)%.c $(HEADERB) | $(OBJF)
			@$(CC) $(CFLAGS) $(INCLUDEB) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

bonus:		$(NAMEB)

$(NAMEB):	make_libs $(OBJB)
			@$(CC) $(CFLAGS) $(INCLUDEB) $(OBJB) -Lft_printf -l$(LIB) -o $(NAMEB)
			@echo "pipex_bonus compiled!"

clean:
			@$(RM) -rf $(OBJ_DIR)
			@make clean -C $(FT_PRINTF)
			@make clean -C $(LIBFT)
			
fclean:		clean
			@$(RM) -f $(NAME)
			@$(RM) -f $(NAMEB)
			@$(RM) -f $(LIBFT)/libft.a
			@$(RM) -f $(FT_PRINTF)/libftprintf.a
				
			
re:			fclean all

.PHONY:		all clean fclean re