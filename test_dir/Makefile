NAME = success_test
NGNAME = ng_test

CC = gcc

# CFLAGS = -Werror -Wall -Wextra

SRCS = success.c
NGSRCS = ng.c

OBJS = $(SRCS:.c=.o)
NGOBJS = $(NGSRCS:.c=.o)

all: $(NAME) $(NGNAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(NGNAME): $(NGOBJS)
	$(CC) $(CFLAGS) $(NGOBJS) -o $(NGNAME)

clean:
	rm -f $(OBJS) $(NGOBJS)

fclean: clean
	rm -f $(NAME) $(NGNAME)

re: fclean all
