/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:47:18 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/28 12:16:10 by jkauker          ###   ########.fr       */
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

# define PROMPT_SUCCESS "🟢 \033[0;36mminishell \033[0;31m➜ \033[0;33m"
# define PROMPT_FAILURE "🔴 \033[0;36mminishell \033[0;31m➜ \033[0;33m"
# define PROMPT_HELLO "👋 \033[0;36mminishell \033[0;31m➜ \033[0;33m"
# define NONE 0
# define PIPE 1
# define OR 2
# define AND 3
# define REDIRECT_IN 4
# define REDIRECT_OUT 5
# define REDIRECT_OUT_APPEND 6
# define REDIRECT_IN_DELIMITER 7
# define OPEN_PAREN 8
# define CLOSE_PAREN 9

# define CMD_SUCCESS 0
# define CMD_FAILURE 1
# define CMD_IMPROP 2
# define CMD_NOT_FOUND 127

extern bool *g_run;

typedef struct s_env_var
{
	char				*name;
	char				*value;
	bool				is_envp;
	struct s_env_var	*next;
	struct s_env_var	*prev;
}			t_env_var;

typedef struct s_shell
{
	bool		run;
	char		*path;
	t_env_var	*env_vars;
}			t_shell;

typedef struct s_shunting_node
{
	char					*value;
	char					**args;
	int						*type;
	int						*priority;
	int						*fd;
	int						*exit_status; // 0 = success, 1 = failure, -1 = not ran yet
	struct s_shunting_node	*next;
	struct s_shunting_node	*prev;
}	t_shunting_node;

typedef struct s_shunting_yard
{
	t_shunting_node			*input;
	t_shunting_node			*output;
	t_shunting_node			*stack;
}	t_shunting_yard;

// command hanling
int				run_command(t_shell *shell, t_shunting_node *cmd);
int				run_path_command(t_shell *shell, t_shunting_node *cmd);
int				execute_commands(t_shunting_yard *yard, t_shell *shell,
					int status);

// old
int				command_loop(t_shell *shell);
int				command_handler(t_shell *shell, char *line);

// Parsing
char			*ft_strncpy(char *dest, const char *src, size_t n);
int				is_shell_op(char *str, char *shell_op[], int size);
t_shunting_yard	*shunting_yard_create(char	**tokens);
t_shunting_yard	*shunting_yard(char **tokens);
void			print_all_stacks(t_shunting_yard *yard);

// builtins
int				ft_cd(t_shunting_node *cmd, t_shell *shell);
int				pwd(void);
int				ft_export(t_shell *shell, t_shunting_node *cmd);
int				ft_unset(t_shunting_node *cmd, t_shell *shell);
int				ft_env(t_shell *shell);
int				ft_exit(t_shell *shell);
int				ft_echo(t_shunting_node *cmd);

// exec env commands
int				run_env_command(t_shell *shell, t_shunting_node *cmd);
void			env_pop(t_env_var *vars, t_env_var *pop);
void			env_push(t_env_var *vars, t_env_var *new_var);
char			**env_to_envp(t_env_var *var);
char			**env_get_path(t_env_var *vars);
t_env_var		*env_get_by_name(t_env_var *vars, char *name);
t_env_var		*env_create_var(char *name, char *value, bool is_envp);
t_env_var		*env_make_vars(char **envp);

//our commands
int				display_history(void);
int				ft_clear(void);

//utils
void			print_invalid_cmd(char *command);
char			**ft_split_shell(const char *str);
void			*free_split(char **split);
void			free_node(t_shunting_node *node);
int				is_operator(char *str);
void			*make_cmds(char *line, t_shell *shell, int i);
char			**filter_variables(char **split, t_shell *shell);
void			free_cmds_helper(t_env_var *cmds);
char			**clean_data(char **temp, char **result);
int				str_is_equal(char *str1, char *str2);
char			*is_valid_input(char *line);
char			**doublestrdup(char **str);
char			*get_matching_files(char *pattern);
char			**split_first_occ(char *str, char c);
int				get_quote_cout(char *str, char quote);

// pipes
int				run_pipe_cmd(t_shunting_node *cmd1, t_shunting_node *cmd2,
					t_shell *shell);
char			**make_env_args(char *cmd, char **args);
char			*get_env_path_to_cmd(t_shell *shell, char *cmd);

//signals
void			signal_handler(int signum);

#endif