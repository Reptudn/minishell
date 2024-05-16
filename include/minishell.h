/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:47:18 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 11:23:59 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "colors.h"
# include "fancy.h"
# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/get_next_line/get_next_line.h"

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
# include <sys/select.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdbool.h>

# define PROMPT_SUCCESS "🟢 \033[0;36mminishell \033[0;31m➜ \033[0m"
# define PROMPT_FAILURE "🔴 \033[0;36mminishell \033[0;31m➜ \033[0m"
# define PROMPT_HELLO "👋 \033[0;36mminishell \033[0;31m➜ \033[0m"
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

# define GARBAGE_COLLECTOR_SIZE 100
# define GARBAGE_CREATE 0
# define GARBAGE_ADD 1
# define GARBAGE_FREE 2

# define PIPE_BUFFER_SIZE 4096

void			ft_garbage_collector(void *ptr, int action);

char			*prompt_success(void);
char			*prompt_failure(void);
char			*prompt_hello(void);
char			*prompt_squote(void);
char			*prompt_dquote(void);

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
	char		*path;
	t_env_var	*env_vars;
	int			*exit_status;
}			t_shell;

typedef struct s_shunting_node
{
	char					*value;
	char					**args;
	int						*type;
	int						*priority;
	int						update;
	int						*exit_status;
	struct s_shunting_node	*next;
	struct s_shunting_node	*prev;
}	t_shunting_node;

typedef struct s_shunting_yard
{
	t_shunting_node			*input;
	t_shunting_node			*output;
	t_shunting_node			*stack;
}	t_shunting_yard;

typedef struct s_temps
{
	int			int_i;
	int			int_j;
	int			int_k;
	int			int_l;
	char		*charp_i;
	char		*charp_j;
	char		*charp_k;
	char		*charp_l;
	t_env_var	*env_var1;
	t_env_var	*env_var2;
}	t_temps;

typedef struct s_prompt
{
	int		original_pos;
	int		col;
	char	*move_cursor;
	int		position;
	char	term_buffer[2048];
	char	*term_type;
}	t_prompt;

typedef struct s_process
{
	const char	*str;
	int			*i;
	t_temps		*temp;
}	t_process;

typedef struct s_delimiter
{
	int	pipefd[2];
	int	pipefd_back[2];
}	t_delimiter;

typedef struct s_handler
{
	int				index;
	int				operator_count;
	int				exit_status;
	int				i;
	t_shunting_node	*operator;
}	t_handler;

typedef struct s_strjoin_many
{
	char	*str;
	char	*temp_str;
	char	*temp;
	int		i;
}	t_strjoin_many;

typedef struct s_process_string
{
	t_temps	temp;
	char	**shell_op;
	int		i;
	char	quote;
	int		returnvalue;
}	t_process_string;

t_shell			*get_shell(void);
int				*get_run(void);
char			*get_input(char *prompt);

// command handling
int				run_command(t_shell *shell, t_shunting_node *cmd);
int				run_path_command(t_shell *shell, t_shunting_node *cmd);
void			print_cmd_chain(t_shunting_node **chain);
int				execute_commands(t_shunting_yard *yard, t_shell *shell);
void			pop_cmd_chain(t_shunting_yard *yard, t_shunting_node **chain,
					int len, int type);
void			print_shunting_node(t_shunting_node *node, int a);

// old
int				command_loop(t_shell *shell);
int				command_handler(t_shell *shell, char *line);

// Parsing
t_shunting_yard	*shunting_yard_create(char	**tokens);
t_shunting_yard	*shunting_yard(char **tokens);
char			*ft_strncpy(char *dest, const char *src, size_t n);
int				is_shell_op(char *str, char *shell_op[], int size);
void			print_all_stacks(t_shunting_yard *yard);
char			**split_first_occ(char *str, char c);

// builtins
int				ft_cd(t_shunting_node *cmd, t_shell *shell, char *new_path);
int				pwd(void);
int				ft_export(t_shell *shell, t_shunting_node *cmd);
int				ft_unset(t_shunting_node *cmd, t_shell *shell);
int				ft_env(void);
int				ft_exit(t_shell *shell, t_shunting_node *cmd);
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
bool			arg_is_numerical(char *arg);

//our commands
int				display_history(void);
int				ft_clear(void);

//utils
void			print_invalid_cmd(char *command, char *error, int status);
char			**ft_split_shell(const char *str);
void			process_string(const char *str, char **result, int *res_i);
char			**fill_shell_op(void);
void			*free_split(char **split);
char			**clean_quotes(char **tmp);
void			free_node(t_shunting_node *node);
int				is_operator(char *str);
void			*make_cmds(char *line, t_shell *shell, int i);
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
					t_shell *shell, int in_fd);
char			**make_env_args(char *cmd, char **args);
char			*get_env_path_to_cmd(t_shell *shell, char *cmd);

//signals
sig_atomic_t	*sigint_recv(void);
void			signal_handler(int signum);
void			signal_restore_parent(void);
void			signal_ignore_parent(void);
void			segfault(int signal);

//garbage collector
void			*ft_malloc(size_t size);
void			free_all(void);
void			ft_free(void *ptr);

// var utils
void			replace_variable(char **value, char ***args);
char			*get_var_str(char *str);

// libft extended
void			*ft_free_many(void *return_val, int count, ...);
char			*ft_strjoin_many(int count, ...);
void			*ft_realloc(void *ptr, size_t size);

#endif