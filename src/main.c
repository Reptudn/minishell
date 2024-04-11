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

int	g_run = 1;

void	print_start_logo(void)
{
	printf("\033[H\033[J%s%s", COLOR_BG_GREEN, COLOR_MAGENTA);
	printf(" __    __     __     __   __     __     "
		"______     __  __     ______     __         __ \n");
	printf("/\\ '-./  \\   /\\ \\   /\\ '-.\\ \\   /"
		"\\ \\   /\\  ___\\   /\\ \\_\\ \\   /\\  ___\\   /\\ \\"
		"       /\\ \\       \n");
	printf("\\ \\ \\-./\\ \\  \\ \\ \\  \\ \\ \\-.  "
		"\\  \\ \\ \\  \\ \\___  \\  \\ \\  __ \\  \\ \\  __\\   "
		"\\ \\ \\____  \\ \\ \\____  \n");
	printf(" \\ \\_\\ \\ \\_\\  \\ \\_\\  \\ \\_\\\\'"
		"\\_\\  \\ \\_\\  \\/\\_____\\  \\ \\_\\ \\_\\  \\ \\_____\\  \\ "
		"\\_____\\  \\ \\_____\\ \n");
	printf("  \\/_/  \\/_/   \\/_/   \\/_/ \\/_/   "
		"\\/_/   \\/_____/   \\/_/\\/_/   \\/_____/   \\/_____/   "
		"\\/_____/ \n\n");
	printf("                                 "
		"by %s\033]8;;https://profile.intra.42.fr/users/jkauker\ajkauker\033]8;"
		";\a%s and "
		"%s\033]8;;https://profile.intra.42.fr/users/nsabia\ansabia\033]8;"
		";\a%s\n\n",
		COLOR_RED, COLOR_MAGENTA, COLOR_RED, COLOR_RESET);
	printf("%s", COLOR_RESET);
	printf("\n%sWelcome %s✨ %s ✨%s\n\n", COLOR_MAGENTA, COLOR_GREEN,
		getenv("USER"), COLOR_RESET);
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
	{
		free(envp);
		return (NULL);
	}
	return (envp);
}

void	env_destroy(t_env_var *env)
{
	t_env_var	*temp;

	if (!env)
		return ;
	while (env)
	{
		free(env->name);
		free(env->value);
		temp = env->next;
		free(env);
		env = temp;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	shell.run = true;
	g_run = 1;
	shell.path = getcwd(NULL, 0);
	shell.exit_status = malloc(sizeof(int));
	*shell.exit_status = CMD_SUCCESS;
	argc++;
	(void)argv;
	if (!shell.path)
	{
		ft_putstr_fd("Error: current working directory\n", STDERR_FILENO);
		return (CMD_FAILURE);
	}
	shell.env_vars = env_make_vars(envp);
	if (!shell.env_vars)
	{
		ft_putstr_fd("Error: environment\n", STDERR_FILENO);
		return (CMD_FAILURE);
	}
	if (signal(SIGINT, signal_handler) == SIG_ERR
		|| signal(SIGQUIT, signal_handler) == SIG_ERR)
	{
		ft_putstr_fd("Error: signal handler\n", STDERR_FILENO);
		free(shell.path);
		return (CMD_FAILURE);
	}
	print_start_logo();
	command_loop(&shell);
	free(shell.path);
	env_destroy(shell.env_vars);
	return (*shell.exit_status);
}

// TODO: echo '"$USER"' has to print "$USER" and not the user
// TODO: sometimes when running pipes or redirections or anything like that that write into a file there will be written stupid stuff aka color codes
// FIXME: color codes are being printed into the pipe too which shouldnt happen