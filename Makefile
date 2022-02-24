NAME = term3d

CC = gcc

#CFLAGS = -O3 -Werror -Wall -Wextra
CFLAGS = -O3 -Werror -Wall -Wextra -g -fsanitize=address
SRCS = main.c \
calc_crossing_eye_dir_and_face.c \
vector.c \
parse_ply.c \
vector_operations.c \
loop_draw.c \
shade.c \
simple_operation.c \

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
