/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_single.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:27:22 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/20 10:49:07 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_command(t_shell *shell, t_command *cmd)
{
	int	status;

	status = CMD_SUCCESS;
	if (str_is_equal(cmd->command, "history"))
		display_history();
	else if (str_is_equal(cmd->command, "exit"))
		shell->run = false;
	else if (str_is_equal(cmd->command, "echo"))
		status = ft_echo(cmd);
	else if (str_is_equal(cmd->command, "pwd"))
		status = pwd();
	else if (str_is_equal(cmd->command, "clear"))
		status = ft_clear();
	else if (str_is_equal(cmd->command, "export"))
		status = ft_export(shell);
	else if (str_is_equal(cmd->command, "env"))
		status = ft_env(shell);
	else if (str_is_equal(cmd->command, "unset"))
		status = ft_unset();
	else if (str_is_equal(cmd->command, "cd"))
		status = ft_cd(cmd, shell);
	else
	{
		status = run_env_command(shell, cmd);
		if (status == CMD_FAILURE)
		{
			status = run_path_command(shell, cmd);
			if (status == CMD_FAILURE)
				print_invalid_cmd(cmd->command);
		}
	}
	return (status);
}
