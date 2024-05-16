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
char	**get_env(void);
int		setup_signals(t_shell *shell);
void	run_shell(t_shell *shell);

int	add_pwd(void)
{
	char		*pwd;
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
		ft_free((pwd));
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
		ft_free((path));
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

int	initialize_shell(t_shell *shell, int argc, char **argv, char **envp)
{
	*get_run() = 1;
	shell->path = getcwd(NULL, 0);
	shell->exit_status = ft_malloc(sizeof(int));
	*shell->exit_status = CMD_SUCCESS;
	argc++;
	(void)argv;
	if (!shell->path || setup_environment(shell, envp) == CMD_FAILURE
		|| setup_signals(shell) == CMD_FAILURE || !shell->exit_status)
		return (CMD_FAILURE);
	return (CMD_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int		init_status;

	rl_catch_signals = 0;
	shell = get_shell();
	init_status = initialize_shell(shell, argc, argv, envp);
	if (init_status == CMD_FAILURE)
		return (CMD_FAILURE);
	run_shell(shell);
	if (isatty(STDIN_FILENO))
		printf("exit\n");
	init_status = *shell->exit_status;
	if (shell->exit_status)
		ft_free((shell->exit_status));
	free_all();
	return (init_status);
}
