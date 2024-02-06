/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:47:18 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/06 13:30:51 by jkauker          ###   ########.fr       */
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

# define PROMPT "\033[0;36mminishell ➜ \033[0;33m"
# define NONE -1
# define PIPE 0
# define OR 1
# define AND 2
# define REDIRECT_IN 3
# define REDIRECT_OUT 4
# define REDIRECT_OUT_APPEND 5
# define REDIRECT_IN_DELIMITER 6

typedef struct s_shell
{
	bool		run;
	char		*path;
	char		**env;
	char		**envp;
}			t_shell;

typedef struct s_command
{
	char				*command;
	char				**args;
	int					*operator_type;
	struct s_command	*next;
	struct s_command	*prev;
	t_shell				*shell;
}			t_command;

int			command_loop(t_shell *shell);
int			command_handler(t_shell *shell, char *line);

// Parsing
char		*ft_strncpy(char *dest, const char *src, size_t n);
int			is_shell_op(char *str, char *shell_op[], int size);

// builtins
int			cd(t_command *cmd, t_shell *shell);
int			ft_cd(t_command *cmd);
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
void		free_cmds(t_command *cmds);
char		**clean_data(char **temp, char ** result);
int			str_is_equal(char *str1, char *str2);
int			is_valid_input(char **split, char *line);

//signals
void		signal_handler(int signum);

#endif