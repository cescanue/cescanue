NAME		= so_long
NAMEB		= so_long_bonus
INCLUDE		= includes
MLXLIB		= mlx
SRC_DIR		= srcs/
SRC_DIRB	= srcs/bonus/
OBJ_DIR		= obj/
CC			= cc
CFLAGS		= -Werror -Wall -Wextra -I
CFLAGSL		= -framework OpenGL -framework AppKit -w -Wall -Wextra -I
RM			= rm -f
LIB			= so_long
SRC_FILES	= so_long \
			  so_long_error \
			  get_next_line \
			  so_long_map \
			  so_long_map1 \
			  so_long_map2 \
			  so_long_imgs \
			  so_long_lst \
			  so_long_windows \
			  so_long_game \
			  so_long_game1 \
			  so_long_hooks \
			  so_long_pl \
			  so_long_pl2 \
			  so_long_awards \
			  so_long_numbers \

SRC_FILESB	= so_long_bonus \
			  so_long_error_bonus \
			  get_next_line_bonus \
			  so_long_map_bonus \
			  so_long_map1_bonus \
			  so_long_map2_bonus \
			  so_long_imgs_bonus \
			  so_long_lst_bonus \
			  so_long_windows_bonus \
			  so_long_game_bonus \
			  so_long_game1_bonus \
			  so_long_hooks_bonus \
			  so_long_pl_bonus \
			  so_long_pl2_bonus \
			  so_long_awards_bonus \
			  so_long_numbers_bonus \
			  so_long_enemy_bonus \
			  so_long_enemy2_bonus \
			  so_long_lives_bonus \
			  so_long_fire_bonus \
			  
HEADER		=	includes/so_long.h \

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
OBJB 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILESB)))


OBJF		=	.cache_exists

all:		make_libs $(NAME)

make_libs:
			@make --no-print-directory -C $(MLXLIB)

$(NAME):	$(OBJ) mlx/libso_long.a
			@$(CC) $(CFLAGSL) $(INCLUDE) $(OBJ) -Lmlx -l$(LIB) -o $(NAME)
			@echo "so_long compiled!"
			
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) | $(OBJF)
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIRB)%.c $(HEADER) | $(OBJF)
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

bonus:		make_libs $(NAMEB)

$(NAMEB):	$(OBJB) mlx/libso_long.a
			@$(CC) $(CFLAGSL) $(INCLUDE) $(OBJB) -Lmlx -l$(LIB) -o $(NAMEB)
			@echo "so_long_bonus compiled!"

clean:
			@$(RM) -rf $(OBJ_DIR)
			@make fclean --no-print-directory -C $(MLXLIB)
			
fclean:		clean
			@$(RM) -f $(NAME)
			@$(RM) -f $(NAMEB)		
			
re:			fclean all

.PHONY:		all clean fclean re