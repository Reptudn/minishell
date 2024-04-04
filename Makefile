NAME	:= minishell

CFLAGS	:= -Wextra -Wall -Werror

HEADERS	:= -I ./include

SRCDIR := ./src/

SRCS	:=  $(SRCDIR)main.c \
			$(SRCDIR)input.c \
			$(SRCDIR)utils/split.c \
			$(SRCDIR)utils/split_helper.c \
			$(SRCDIR)utils/command_error.c \
			$(SRCDIR)utils/make_cmds.c \
			$(SRCDIR)utils/make_cmds_helper.c \
			$(SRCDIR)utils/free_split_cmds.c \
			$(SRCDIR)utils/command_utils.c \
			$(SRCDIR)utils/input_validation.c \
			$(SRCDIR)utils/environment.c \
			$(SRCDIR)utils/wildcard.c \
			$(SRCDIR)utils/variables.c \
			$(SRCDIR)commands/show_history.c \
			$(SRCDIR)commands/clear.c \
			$(SRCDIR)commands/env_commands.c \
			$(SRCDIR)builtin/unset.c \
			$(SRCDIR)builtin/exit.c \
			$(SRCDIR)builtin/echo.c \
			$(SRCDIR)builtin/pwd.c \
			$(SRCDIR)builtin/env.c \
			$(SRCDIR)builtin/export.c \
			$(SRCDIR)builtin/cd.c \
			$(SRCDIR)signals/signal_handler.c \
			$(SRCDIR)handle_commands/and.c \
			$(SRCDIR)handle_commands/append.c \
			$(SRCDIR)handle_commands/delimiter.c \
			$(SRCDIR)handle_commands/handler.c \
			$(SRCDIR)handle_commands/pipe.c \
			$(SRCDIR)handle_commands/or.c \
			$(SRCDIR)handle_commands/path_cmd.c \
			$(SRCDIR)handle_commands/redirect_in.c \
			$(SRCDIR)handle_commands/redirect_out.c \
			$(SRCDIR)handle_commands/run_single.c \
			$(SRCDIR)handle_commands/execute_pipe_chain.c \
			$(SRCDIR)shunting_yard/shunting_yard.c \
			$(SRCDIR)shunting_yard/shunting_yard_utils.c \
			$(SRCDIR)shunting_yard/shunting_stack_utils.c \
			$(SRCDIR)shunting_yard/ast_utils.c

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

get_next_line:
	@make -C ./lib/get_next_line

$(OBJDIR)%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) libft ft_printf get_next_line
	$(CC) $(OBJS) ./lib/libft/libft.a ./lib/get_next_line/get_next_line.a ./lib/ft_printf/libftprintf.a $(HEADERS) -lreadline -o $(NAME) && printf "\n\nCompilation finished!\n"

clean:
	@make -C ./lib/libft clean
	@make -C ./lib/ft_printf clean
	@make -C ./lib/get_next_line clean
	@rm -rf $(OBJDIR)

fclean: clean
	@make -C ./lib/libft fclean
	@make -C ./lib/ft_printf fclean
	@make -C ./lib/get_next_line fclean
	@rm -rf $(NAME)

debug: CFLAGS += -g -O0
debug: $(NAME)

re: fclean all