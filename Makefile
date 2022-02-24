NAME = term3d

CC = gcc

CFLAGS = -O3 -Werror -Wall -Wextra -g -fsanitize=address -Iinclude
SRCS = srcs/main.c \
srcs/calc_crossing_eye_dir_and_face.c \
srcs/vector.c \
srcs/parse_ply.c \
srcs/vector_operations.c \
srcs/loop_draw.c \
srcs/shade.c \
srcs/simple_operation.c \

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
