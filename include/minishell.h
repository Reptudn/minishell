/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:47:18 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/06 15:25:09 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "colors.h"
# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdbool.h>

# define PROMPT "🪄  \033[0;36mminishell \033[0;31m➜ \033[0;33m"
# define NONE 0
# define PIPE 1
# define OR 2
# define AND 3
# define REDIRECT_IN 4
# define REDIRECT_OUT 5
# define REDIRECT_OUT_APPEND 6
# define REDIRECT_IN_DELIMITER 7
# define COMMAND 8

# define CMD_SUCCESS 0
# define CMD_FAILURE 1
# define INVLAID_TOKEN 2

typedef struct s_variable
{
	char				*name;
	char				*value;
	struct s_variable	*next;
	struct s_variable	*prev;
}			t_variable;

typedef struct s_shell
{
	bool		run;
	char		*path;
	char		**env;
	char		**envp;
	t_variable	*variables;
}			t_shell;

typedef struct s_command
{
	char				*command;
	char				**args;
	int					*operator_type;
	int					priority;
	struct s_command	*next;
	struct s_command	*prev;
	t_shell				*shell;
}			t_command;

typedef struct s_shunting_node
{
	char					*value;
	char					**args;
	int						*type;
	int						*priority;
	struct s_shunting_node	*next;
	struct s_shunting_node	*prev;
}	t_shunting_node;

typedef struct	s_shunting_yard
{
	t_shunting_node			*input;
	t_shunting_node			*output;
	t_shunting_node			*stack;
}	t_shunting_yard;

// command hanling
int			run_command(t_shell *shell, t_command *cmd);
int			run_path_command(t_shell *shell, t_command *cmd);
int			execute_commands(t_shell *shell, t_command *cmd1, t_command *cmd2);

// old
int			command_loop(t_shell *shell);
int			command_handler(t_shell *shell, char *line);

// Parsing
char		*ft_strncpy(char *dest, const char *src, size_t n);
int			is_shell_op(char *str, char *shell_op[], int size);
int			get_operator_priority(char *operator);

// builtins
int			ft_cd(t_command *cmd, t_shell *shell);
int			pwd(void);
int			ft_export(t_shell *shell);
int			ft_unset(void);
int			ft_env(t_shell *shell);
int			ft_exit(t_shell *shell);
int			ft_echo(t_command *cmd);

// exec env commands
int			run_env_command(t_shell *shell, t_command *cmd);

//our commands
int			display_history(void);
int			ft_clear(void);

//utils
void		print_invalid_cmd(char *command);
char		**ft_split_shell(const char *str);
t_command	*free_split(char **split);
int			is_operator(char *str);
t_command	*make_cmds(char *line, t_shell *shell);
char		**filter_variables(char **split, t_shell *shell);
void		free_cmds(t_command *cmds);
void		free_cmds_helper(t_variable *cmds);
char		**clean_data(char **temp, char **result);
int			str_is_equal(char *str1, char *str2);
char		*is_valid_input(char *line);

// pipes
int			run_pipe_cmd(t_command *cmd1, t_command *cmd2, t_shell *shell);

char		**make_env_args(char *cmd, char **args);
char		*get_env_path_to_cmd(t_shell *shell, char *cmd);

//signals
void		signal_handler(int signum);

#endif