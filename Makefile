NAME = term3d

CC = gcc -O3

# CFLAGS = -Werror -Wall -Wextra -g -fsanitize=address
SRCS = main.c \
is_colided.c \
vector.c \
parse_ply.c \
vector_operations.c \
loop_draw.c \
shade.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

ok_test: re
	make -C test_dir
	cd test_dir && ./success_test

fail_test: re
	make -C test_dir
	cd test_dir && ./ng_test

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
