NAME = libasm.a

SRC = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s
OBJ = $(SRC:.s=.o)

NASM = nasm
NASMFLAGS = -f elf64

CC = gcc
CFLAGS = -Wall -Wextra -Werror

%.o: %.s
	$(NASM) $(NASMFLAGS) $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

test: $(NAME) main.c
	$(CC) $(CFLAGS) main.c -L. -lasm -o test_program

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) test_program

re: fclean all

.PHONY: all clean fclean re test
