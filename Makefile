NAME	:= minishell

CFLAGS	:= -Wextra -Wall -Werror -gdwarf-4 -g

HEADERS	:= -I ./include

SRCDIR := ./src/

SRCS	:=  $(SRCDIR)main.c \
			$(SRCDIR)input.c \
			$(SRCDIR)utils/split.c \
			$(SRCDIR)utils/split_helper.c \
			$(SRCDIR)utils/command_error.c \
			$(SRCDIR)commands/show_history.c \
			$(SRCDIR)commands/clear.c \
			$(SRCDIR)commands/env_commands.c \
			$(SRCDIR)builtin/exit.c \
			$(SRCDIR)builtin/echo.c \
			$(SRCDIR)builtin/pwd.c \
			$(SRCDIR)signals/signal_handler.c \
			$(SRCDIR)utils/make_cmds.c \

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
	$(CC) $(OBJS) ./lib/libft/libft.a ./lib/ft_printf/libftprintf.a $(HEADERS) -lreadline -o $(NAME) && printf "\n\nCompilation finished!\n"

clean:
	@make -C ./lib/libft clean
	@make -C ./lib/ft_printf clean
	@rm -rf $(OBJS)

fclean: clean
	@make -C ./lib/libft fclean
	@make -C ./lib/ft_printf fclean
	@rm -rf $(NAME)

re: fclean all
