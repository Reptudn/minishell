/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsabia <nsabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 09:30:04 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/17 12:22:41 by nsabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env_destroy(t_env_var *env);
void	print_start_logo(void);

int	setup_signals(t_shell *shell)
{
	(void)shell;
	if (signal(SIGINT, signal_handler) == SIG_ERR
		|| signal(SIGQUIT, signal_handler) == SIG_ERR
		|| signal(SIGTERM, signal_handler) == SIG_ERR
		|| signal(SIGSEGV, segfault) == SIG_ERR)
	{
		ft_putstr_fd("Error: signal handler\n", STDERR_FILENO);
		return (CMD_FAILURE);
	}
	return (CMD_SUCCESS);
}

void	run_shell(t_shell *shell)
{
	if (isatty(fileno(stdin)))
		print_start_logo();
	command_loop(shell);
	env_destroy(shell->env_vars);
}
