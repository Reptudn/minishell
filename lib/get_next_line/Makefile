CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

NAME = get_next_line.a

.PHONY: all clean clean re

all: $(NAME)

$(NAME): $(OBJS)
		ar -rcs $(NAME) $(OBJS)

clean:
		rm -rf $(OBJS)

fclean: clean
		rm -f $(NAME)
	
re: fclean all