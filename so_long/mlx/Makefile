NAME		= libso_long.a
INCLUDE		= includes
LIBFT_PRINTF= ft_printf
SRC_DIR		= srcs/
OBJ_DIR		= obj/
CC			= cc
CFLAGS		= -O2 -DSTRINGPUTX11 -w -I
AR			= ar rcs
SRC_FILES_C	= mlx_shaders mlx_xpm mlx_int_str_to_wordtab mlx_png 
SRC_FILES_M	= mlx_new_window mlx_init_loop mlx_new_image mlx_mouse

HEADER		=	includes/mlx.h

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES_C)))
SRC1		= 	$(addprefix $(SRC_DIR), $(addsuffix .m $(SRC_FILES_M)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES_C)))
OBJ1 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES_M)))

OBJF		=	.cache_exists

all:		make_libs $(NAME)

make_libs:
			@make -C $(LIBFT_PRINTF)

$(NAME):	$(OBJ) $(OBJ1) ft_printf/libftprintf.a
			@cp ft_printf/libftprintf.a .
			@mv libftprintf.a $(NAME)
			@$(AR) $(NAME) $(OBJ) $(OBJ1)
			@ranlib	$(NAME)
			@echo "MLXLIB compiled!"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) | $(OBJF)
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.m $(HEADER) | $(OBJF)
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

bonus:		all

clean:
			@$(RM) -rf $(OBJ_DIR)
			@make fclean -C $(LIBFT_PRINTF)
			
fclean:		clean
			@$(RM) -f $(NAME)
			
re:			fclean all

.PHONY:		all clean fclean re