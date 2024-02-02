NAME	:= minishell

CFLAGS	:= -Wextra -Wall -Werror

HEADERS	:= -I ./include

LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCDIR := ./src/

SRCS	:=  $(SRCDIR)main.c \
			$(SRCDIR)input.c \
			$(SRCDIR)/utils/split.c \

OBJS	:= ${SRCS:.c=.o}

CC		:= cc

.PHONY: all, clean, fclean, re

all: $(NAME)

libft:
	@make -C ./lib/libft

ft_printf:
	@make -C ./lib/ft_printf


%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) libft ft_printf
	$(CC) $(OBJS) $(LIBS) ./lib/libft/libft.a ./lib/ft_printf/libftprintf.a $(HEADERS) -o $(NAME) && printf "Compilation finished!\n"

clean:
	@make -C ./lib/libft clean
	@make -C ./lib/ft_printf clean
	@rm -rf $(OBJS)

fclean: clean
	@make -C ./lib/libft fclean
	@make -C ./lib/ft_printf fclean
	@rm -rf $(NAME)

re: fclean all
