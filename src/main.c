/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:03:48 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/16 10:24:14 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_start_logo()
{
	printf("\033[H\033[J%s%s", COLOR_BG_GREEN, COLOR_MAGENTA);
	printf(" __    __     __     __   __     __     ______     __  __     ______     __         __ \n");
	printf("/\\ '-./  \\   /\\ \\   /\\ '-.\\ \\   /\\ \\   /\\  ___\\   /\\ \\_\\ \\   /\\  ___\\   /\\ \\       /\\ \\       \n");
	printf("\\ \\ \\-./\\ \\  \\ \\ \\  \\ \\ \\-.  \\  \\ \\ \\  \\ \\___  \\  \\ \\  __ \\  \\ \\  __\\   \\ \\ \\____  \\ \\ \\____  \n");
	printf(" \\ \\_\\ \\ \\_\\  \\ \\_\\  \\ \\_\\\\'\\_\\  \\ \\_\\  \\/\\_____\\  \\ \\_\\ \\_\\  \\ \\_____\\  \\ \\_____\\  \\ \\_____\\ \n");
	printf("  \\/_/  \\/_/   \\/_/   \\/_/ \\/_/   \\/_/   \\/_____/   \\/_/\\/_/   \\/_____/   \\/_____/   \\/_____/ \n\n");
	printf("                                 by %sjkauker%s and %snsabia%s\n\n", COLOR_RED, COLOR_MAGENTA, COLOR_RED, COLOR_RESET);
	printf("%s", COLOR_RESET);
}

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
	print_start_logo();
	command_loop(&shell);
	free(shell.path);
	return (0);
}
