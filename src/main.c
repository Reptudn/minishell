/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:03:48 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/05 14:57:50 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_env(void)
{
	char	*env;
	char	**envp;

	env = getenv("PATH");
	if (!env)
		return (NULL);
	envp = ft_split(env, ':');
	if (!envp)
		return (NULL);
	return (envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	shell.run = true;
	shell.path = getcwd(NULL, 0);
	shell.envp = envp;
	argc++;
	argv = 0;
	if (!shell.path)
	{
		ft_putstr_fd("Error: current working directory\n", STDERR_FILENO);
		return (1);
	}
	shell.env = get_env();
	if (!shell.env)
	{
		ft_putstr_fd("Error: environment\n", STDERR_FILENO);
		return (1);
	}
	if (signal(SIGINT, signal_handler) == SIG_ERR || signal(SIGQUIT, signal_handler) == SIG_ERR)
	{
		ft_putstr_fd("Error: signal handler\n", STDERR_FILENO);
		free(shell.path);
		return (1);
	}
	command_loop(&shell);
	free(shell.path);
	return (0);
}
