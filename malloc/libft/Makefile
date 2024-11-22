NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

SRC = ft_strnstr.c ft_isdigit.c ft_lstadd_back.c ft_putstr_fd.c ft_lstnew.c ft_strlcpy.c ft_strlen.c ft_lstlast.c ft_lstfind.c ft_memcmp.c ft_putnbr_fd.c ft_lstclear.c ft_lstiter.c ft_strchr.c ft_striteri.c ft_bzero.c ft_strjoin.c ft_isascii.c ft_memcpy.c ft_isprint.c ft_putendl_fd.c ft_lstmap.c ft_lstsize.c ft_toupper.c ft_split.c ft_lstadd_front.c ft_strrchr.c ft_isalpha.c ft_memchr.c ft_putchar_fd.c ft_memset.c ft_substr.c ft_strncmp.c ft_strmapi.c ft_strtrim.c ft_memmove.c ft_strlcat.c ft_calloc.c ft_isnbr.c ft_strdup.c ft_atoi.c ft_isalnum.c ft_lstdelone.c ft_itoa.c ft_tolower.c ft_strnstr.c ft_isdigit.c ft_lstadd_back.c ft_putstr_fd.c ft_lstnew.c ft_strlcpy.c ft_strlen.c ft_lstlast.c ft_lstfind.c ft_memcmp.c ft_putnbr_fd.c ft_lstclear.c ft_lstiter.c ft_strchr.c ft_striteri.c ft_bzero.c ft_strjoin.c ft_isascii.c ft_memcpy.c ft_isprint.c ft_putendl_fd.c ft_lstmap.c ft_lstsize.c ft_toupper.c ft_split.c ft_lstadd_front.c ft_strrchr.c ft_isalpha.c ft_memchr.c ft_putchar_fd.c ft_memset.c ft_substr.c ft_strncmp.c ft_strmapi.c ft_strtrim.c ft_memmove.c ft_strlcat.c ft_calloc.c ft_isnbr.c ft_strdup.c ft_atoi.c ft_isalnum.c ft_lstdelone.c ft_itoa.c ft_tolower.c ft_printf_getvalues.c ft_printf_utils.c ft_printf_getvalues2.c ft_printf.c ft_printf_parse.c ft_printf_format2.c ft_printf_format.c ft_printf_numbers.c
OBJ = $(SRC:.c=.o)

all: $(NAME)
	@echo "Compiling libft..."
	@echo "libft compiled successfully."

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	@$(RM) $(OBJ)
	@echo "Object files removed."

fclean: clean
	@echo "Removing libft..."
	@$(RM) $(NAME)
	@echo "libft removed."

re: fclean all
	@echo "Recompilation of libft completed."
