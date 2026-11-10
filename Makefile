NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -Iincludes

SRC_DIR = src
SRC = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/parser.c \
	$(SRC_DIR)/parser_utils.c \
	$(SRC_DIR)/analysis.c \
	$(SRC_DIR)/stack_ops.c \
	$(SRC_DIR)/exec_op.c \
	$(SRC_DIR)/sort_utils.c \
	$(SRC_DIR)/simple.c \
	$(SRC_DIR)/medium.c \
	$(SRC_DIR)/complex.c \
	$(SRC_DIR)/adaptive.c \
	$(SRC_DIR)/bench.c \
	$(SRC_DIR)/output_utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c includes/push_swap.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
