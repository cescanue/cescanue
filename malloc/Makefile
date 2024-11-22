# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -Werror -pthread -fPIC
LDFLAGS := -shared -pthread

# Define host type if not set in environment
ifneq ($(origin HOSTTYPE), environment)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

# Project structure
NAME_SHARED := libft_malloc_$(HOSTTYPE).so
NAME_STATIC := libft_malloc.a
SYMLINK := libft_malloc.so
LIBFT_DIR := libft
LIBFT_A := $(LIBFT_DIR)/libft.a

# Source files
SRCS := malloc.c
OBJS := $(SRCS:.c=.o)

# Header files
HEADERS := malloc.h

# Colors for pretty output
GREEN := \033[0;32m
BLUE := \033[0;34m
RESET := \033[0m

# Targets
.PHONY: all clean fclean re test testtime mac

all: $(NAME_SHARED) $(SYMLINK)

$(LIBFT_A):
	@printf "$(BLUE)Compiling libft library...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME_SHARED): $(OBJS) $(LIBFT_A)
	@printf "$(BLUE)Creating shared library...$(RESET)\n"
	@$(CC) $(LDFLAGS) -o $@ $(OBJS) -L$(LIBFT_DIR) -lft
	@printf "$(GREEN)Shared library created successfully!$(RESET)\n"

# Modified symlink rule to only update when necessary
$(SYMLINK): $(NAME_SHARED)
	@if [ ! -e $@ ] || [ "$$(readlink $@)" != "$(NAME_SHARED)" ]; then \
		printf "$(BLUE)Updating symbolic link...$(RESET)\n"; \
		ln -sf $(NAME_SHARED) $@; \
	fi

# Updated rule for object files to include header dependency
%.o: %.c $(HEADERS)
	@printf "$(BLUE)Compiling $<...$(RESET)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(BLUE)Removing object files...$(RESET)\n"
	@rm -f $(OBJS)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@printf "$(BLUE)Removing libraries and executables...$(RESET)\n"
	@rm -f $(NAME_SHARED) $(SYMLINK) $(NAME_STATIC) malloctest malloctest_static
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

test: all
	@printf "$(BLUE)Compiling test program...$(RESET)\n"
	$(CC) $(CFLAGS) malloctest.c -o malloctest
	@printf "$(BLUE)Running malloc tests...$(RESET)\n"
	@./run_linux.sh ./malloctest || true

testtime: all
	@printf "$(BLUE)Compiling test program...$(RESET)\n"
	@$(CC) $(CFLAGS) malloctest.c -o malloctest
	@printf "$(BLUE)Running malloc tests with timing...$(RESET)\n"
	@./run_linux.sh /usr/bin/time -v ./malloctest || true

mac: malloctest_static
	@printf "$(BLUE)Running malloc tests with static library...$(RESET)\n"
	@./malloctest_static || true

malloctest_static: $(NAME_STATIC) $(LIBFT_A) malloctest.c
	@printf "$(BLUE)Compiling test program with static library...$(RESET)\n"
	@$(CC) $(CFLAGS) malloctest.c -o $@ $(NAME_STATIC) $(LIBFT_A)

$(NAME_STATIC): $(OBJS)
	@printf "$(BLUE)Creating static library...$(RESET)\n"
	@ar rcs $@ $(OBJS)
	@printf "$(GREEN)Static library created successfully!$(RESET)\n"