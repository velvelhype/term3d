NAME = term3d

CC = gcc

# CFLAGS = -Werror -Wall -Wextra

SRCS = main.c \
is_colided.c \
vector.c \
parse_ply.c \
vector_operations.c \
loop_draw.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

ok_test:
	cd test_dir && ./success_test

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
