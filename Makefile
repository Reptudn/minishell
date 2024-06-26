NAME	:= minishell

CFLAGS	:= -Wextra -Wall -Werror

HEADERS	:= -I ./include

SRCDIR := ./src/

SRCS	:=  $(SRCDIR)main.c \
			$(SRCDIR)input.c \
			$(SRCDIR)input_helper.c \
			$(SRCDIR)setup.c \
			$(SRCDIR)setup_helper.c \
			$(SRCDIR)cheese.c \
			$(SRCDIR)fancy/prompt.c \
			$(SRCDIR)fancy/cursor_utils.c \
			$(SRCDIR)utils/split.c \
			$(SRCDIR)utils/split2.c \
			$(SRCDIR)utils/split_helper.c \
			$(SRCDIR)utils/split_helper2.c \
			$(SRCDIR)utils/command_error.c \
			$(SRCDIR)utils/make_cmds_helper.c \
			$(SRCDIR)utils/free_split_cmds.c \
			$(SRCDIR)utils/command_utils.c \
			$(SRCDIR)utils/input_validation.c \
			$(SRCDIR)utils/environment.c \
			$(SRCDIR)utils/environment2.c \
			$(SRCDIR)utils/environment3.c \
			$(SRCDIR)utils/wildcard.c \
			$(SRCDIR)utils/variables.c \
			$(SRCDIR)utils/variables2.c \
			$(SRCDIR)utils/variables3.c \
			$(SRCDIR)utils/variables4.c \
			$(SRCDIR)commands/show_history.c \
			$(SRCDIR)commands/clear.c \
			$(SRCDIR)commands/env_commands.c \
			$(SRCDIR)commands/env_commands2.c \
			$(SRCDIR)prompts/color.c \
			$(SRCDIR)prompts/color2.c \
			$(SRCDIR)prompts/readline_prompts.c \
			$(SRCDIR)builtin/unset.c \
			$(SRCDIR)builtin/exit.c \
			$(SRCDIR)builtin/exit_helper.c \
			$(SRCDIR)builtin/echo.c \
			$(SRCDIR)builtin/echo_helper.c \
			$(SRCDIR)builtin/pwd.c \
			$(SRCDIR)builtin/env.c \
			$(SRCDIR)builtin/export.c \
			$(SRCDIR)builtin/export_helper.c \
			$(SRCDIR)builtin/cd.c \
			$(SRCDIR)builtin/cd_helper.c \
			$(SRCDIR)signals/signal_handler.c \
			$(SRCDIR)handle_commands/and.c \
			$(SRCDIR)handle_commands/append.c \
			$(SRCDIR)handle_commands/delimiter.c \
			$(SRCDIR)handle_commands/delimiter_helper.c \
			$(SRCDIR)handle_commands/handler.c \
			$(SRCDIR)handle_commands/handler_helper.c \
			$(SRCDIR)handle_commands/pipe.c \
			$(SRCDIR)handle_commands/pipe2.c \
			$(SRCDIR)handle_commands/or.c \
			$(SRCDIR)handle_commands/path_cmd.c \
			$(SRCDIR)handle_commands/redirect_in.c \
			$(SRCDIR)handle_commands/redirect_out.c \
			$(SRCDIR)handle_commands/run_single.c \
			$(SRCDIR)handle_commands/execute_pipe_chain.c \
			$(SRCDIR)handle_commands/execute_pipe_chain_helper.c \
			$(SRCDIR)handle_commands/execute_pipe_chain_helper2.c \
			$(SRCDIR)shunting_yard/shunting_yard.c \
			$(SRCDIR)shunting_yard/shunting_yard2.c \
			$(SRCDIR)shunting_yard/shunting_yard_node.c \
			$(SRCDIR)shunting_yard/shunting_yard_utils.c \
			$(SRCDIR)shunting_yard/shunting_stack_utils.c \
			$(SRCDIR)shunting_yard/shunting_print.c \
			$(SRCDIR)shunting_yard/ast_utils.c

OBJDIR := ./obj/
OBJS	:= $(SRCS:.c=.o)
OBJS	:= $(addprefix $(OBJDIR),$(OBJS))

CC		:= cc

.PHONY: all, clean, fclean, re

all: $(NAME)

libft:
	@make -C ./lib/libft

get_next_line:
	@make -C ./lib/get_next_line

$(OBJDIR)%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) libft get_next_line
	($(CC) $(OBJS) ./lib/libft/libft.a ./lib/get_next_line/get_next_line.a $(HEADERS) -lreadline -lncurses -ltermcap -o $(NAME) && printf "\n\nCompilation finished!\n") || (printf "\n\nCompilation failed!\n")

clean:
	@make -C ./lib/libft clean
	@make -C ./lib/get_next_line clean
	@rm -rf $(OBJDIR)

fclean: clean
	@make -C ./lib/libft fclean
	@make -C ./lib/get_next_line fclean
	@rm -rf $(NAME)

debug: CFLAGS += -g -O0
debug: fclean $(NAME)

re: fclean all

run: all
	./$(NAME)

rerun: re run

norm:
	@cd src && norminette | grep "Error:" | wc -l

norminette: norm

valgrind: debug
	valgrind --leak-check=full ./$(NAME)

unused:
	cppcheck --enable=unusedFunction ./src
