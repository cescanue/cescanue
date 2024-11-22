NAME = ft_ping
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I. -D_GNU_SOURCE
LDFLAGS = -lm

SRC_FILES = ft_ping_main.c \
            ft_ping_utils.c \
            ft_ping_socket.c \
            ft_ping_packet.c \
            ft_ping_display.c \
            ft_ping_signal.c \
            ft_ping_compat.c

OBJ_DIR = obj
OBJ_FILES = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

HEADERS = ft_ping.h

# Colors for prettier output
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ_FILES)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJ_FILES) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)Build complete! $(NAME) is ready.$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@echo "$(GREEN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re