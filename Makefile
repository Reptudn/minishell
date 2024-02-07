NAME	:= minishell

CFLAGS	:= -Wextra -Wall -gdwarf-4 -g

HEADERS	:= -I ./include

SRCDIR := ./src/

SRCS	:=  $(SRCDIR)main.c \
			$(SRCDIR)input.c \
			$(SRCDIR)utils/split.c \
			$(SRCDIR)utils/split_helper.c \
			$(SRCDIR)utils/command_error.c \
			$(SRCDIR)utils/make_cmds.c \
			$(SRCDIR)utils/free_split_cmds.c \
			$(SRCDIR)utils/command_utils.c \
			$(SRCDIR)utils/input_validation.c \
			$(SRCDIR)commands/show_history.c \
			$(SRCDIR)commands/clear.c \
			$(SRCDIR)commands/env_commands.c \
			$(SRCDIR)commands/command_handler.c \
			$(SRCDIR)builtin/unset.c \
			$(SRCDIR)builtin/exit.c \
			$(SRCDIR)builtin/echo.c \
			$(SRCDIR)builtin/pwd.c \
			$(SRCDIR)builtin/env.c \
			$(SRCDIR)builtin/export.c \
			$(SRCDIR)signals/signal_handler.c \

OBJDIR := ./obj/
OBJS	:= $(SRCS:.c=.o)
OBJS	:= $(addprefix $(OBJDIR),$(OBJS))

CC		:= cc

.PHONY: all, clean, fclean, re

all: $(NAME)

libft:
	@make -C ./lib/libft

ft_printf:
	@make -C ./lib/ft_printf

$(OBJDIR)%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) libft ft_printf
	$(CC) $(OBJS) ./lib/libft/libft.a ./lib/ft_printf/libftprintf.a $(HEADERS) -lreadline -o $(NAME) && printf "\n\nCompilation finished!\n"

clean:
	@make -C ./lib/libft clean
	@make -C ./lib/ft_printf clean
	@rm -rf $(OBJDIR)

fclean: clean
	@make -C ./lib/libft fclean
	@make -C ./lib/ft_printf fclean
	@rm -rf $(NAME)

re: fclean all
