/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:03:48 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/20 09:33:24 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	*g_run = NULL;

void	print_start_logo()
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
	g_run = &(shell.run);
	shell.path = getcwd(NULL, 0);
	argc++;
	argv = 0;
	if (!shell.path)
	{
		ft_putstr_fd("Error: current working directory\n", STDERR_FILENO);
		return (1);
	}
	shell.env_vars = env_make_vars(envp, &shell);
	if (!shell.env_vars)
	{
		ft_putstr_fd("Error: environment\n", STDERR_FILENO);
		return (1);
	}
	if (signal(SIGINT, signal_handler) == SIG_ERR
		|| signal(SIGQUIT, signal_handler) == SIG_ERR)
	{
		ft_putstr_fd("Error: signal handler\n", STDERR_FILENO);
		free(shell.path);
		return (1);
	}
	print_start_logo();
	command_loop(&shell);
	free(shell.path);
	env_destroy(shell.env_vars);
	return (0);
}
