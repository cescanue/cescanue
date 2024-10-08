NAME		= minitalk
INCLUDE		= includes
FT_PRINTF	= ft_printf
LIBFT		= ft_printf/libft
SRC_DIR		= srcs/
OBJ_DIR		= obj/
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I
RM			= rm -f
LIB			= ftprintf
SRC_FILES	= server \
			  server2 \
			  client \

SERVERO		= obj/server.o \
			  obj/server2.o \

CLIENTO		= obj/client.o \

HEADER		=	includes/minitalk.h \

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF		=	.cache_exists

all:		make_libs $(NAME)

make_libs:
			@make -C $(FT_PRINTF)

$(NAME):	$(OBJ) ft_printf/libftprintf.a server client
			
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) | $(OBJF)
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

bonus:		all

server:		$(OBJ) ft_printf/libftprintf.a
			@$(CC) $(CFLAGS) $(INCLUDE) $(SERVERO) -Lft_printf -l$(LIB) -o server
			@echo "Server compiled!"

client:		$(OBJ) ft_printf/libftprintf.a
			@$(CC) $(CFLAGS) $(INCLUDE) $(CLIENTO) -Lft_printf -l$(LIB) -o client
			@echo "Client compiled!"

clean:
			@$(RM) -rf $(OBJ_DIR)
			@make clean -C $(FT_PRINTF)
			@make clean -C $(LIBFT)

fclean:		clean
			@$(RM) -f server
			@$(RM) -f client
			@$(RM) -f $(LIBFT)/libft.a
			@$(RM) -f $(FT_PRINTF)/libftprintf.a
			
re:			fclean all

.PHONY:		all clean fclean re