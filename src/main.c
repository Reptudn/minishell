/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:03:48 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 13:41:21 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		handle_shell_depth(t_shell *shell);
void	env_destroy(t_env_var *env);
char	**get_env(void);
void	print_start_logo(void);

int		add_pwd(void)
{
	char	*pwd;
	t_env_var	*pwd_var;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("Error: getcwd\n", STDERR_FILENO);
		return (CMD_FAILURE);
	}
	pwd_var = env_create_var("PWD", pwd, true);
	if (!pwd_var)
	{
		ft_putstr_fd("Error: env_create_var\n", STDERR_FILENO);
		free(pwd);
		return (CMD_FAILURE);
	}
	env_push(get_shell()->env_vars, pwd_var);
	return (CMD_SUCCESS);
}

int	add_minishell_path(void)
{
	char		*path;
	t_env_var	*path_var;

	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_putstr_fd("Error: getcwd\n", STDERR_FILENO);
		return (CMD_FAILURE);
	}
	path_var = env_create_var("MINISHELL_PATH", path, true);
	if (!path_var)
	{
		ft_putstr_fd("Error: env_create_var\n", STDERR_FILENO);
		free(path);
		return (CMD_FAILURE);
	}
	env_push(get_shell()->env_vars, path_var);
	return (CMD_SUCCESS);
}

int	setup_environment(t_shell *shell, char **envp)
{
	if (!envp)
	{
		ft_putstr_fd("Error: environment variables\n", STDERR_FILENO);
		return (CMD_FAILURE);
	}
	shell->env_vars = env_make_vars(envp);
	if (shell->env_vars)
		return (CMD_SUCCESS);
	if (handle_shell_depth(shell) == CMD_FAILURE)
		return (CMD_FAILURE);
	if (add_pwd() == CMD_FAILURE)
		return (CMD_FAILURE);
	if (add_minishell_path() == CMD_FAILURE)
		return (CMD_FAILURE);
	return (CMD_SUCCESS);
}

int	setup_signals(t_shell *shell)
{
	if (signal(SIGINT, signal_handler) == SIG_ERR
		|| signal(SIGQUIT, signal_handler) == SIG_ERR
		|| signal(SIGTERM, signal_handler) == SIG_ERR
		|| signal(SIGSEGV, segfault) == SIG_ERR)
	{
		ft_putstr_fd("Error: signal handler\n", STDERR_FILENO);
		free(shell->path);
		return (CMD_FAILURE);
	}
	return (CMD_SUCCESS);
}

int	initialize_shell(t_shell *shell, int argc, char **argv, char **envp)
{
	*get_run() = 1;
	shell->path = getcwd(NULL, 0);
	shell->exit_status = malloc(sizeof(int));
	*shell->exit_status = CMD_SUCCESS;
	argc++;
	(void)argv;
	if (!shell->path || setup_environment(shell, envp) == CMD_FAILURE
		|| setup_signals(shell) == CMD_FAILURE || !shell->exit_status)
		return (CMD_FAILURE);
	return (CMD_SUCCESS);
}

void	run_shell(t_shell *shell)
{
	if (isatty(fileno(stdin)))
		print_start_logo();
	command_loop(shell);
	if (shell->path)
		free(shell->path);
	env_destroy(shell->env_vars);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int		init_status;

	rl_catch_signals = 0; // TODO: Check if this  prevents some readline functions to not work correclty -> this is only to not print ^C when pressing control + c
	shell = get_shell();
	init_status = initialize_shell(shell, argc, argv, envp);
	if (init_status == CMD_FAILURE)
		return (CMD_FAILURE);
	run_shell(shell);
	if (isatty(STDIN_FILENO))
		printf("exit\n");
	return (*shell->exit_status);
}


// TODO: when running anything with pipes make the parent process ignore SIGINT and SIGQUIT and after the child process is done, reset the signal handlers
// XXX: When saving commands inside a export variable they have to be executed when just calling the variable