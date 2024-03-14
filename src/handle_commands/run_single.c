/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_single.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:27:22 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/13 14:59:18 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_command(t_shell *shell, t_shunting_node *cmd)
{
	int	status;

	if (!cmd || !shell)
		return (CMD_FAILURE);
	status = CMD_SUCCESS;
	if (str_is_equal(cmd->value, "history"))
		display_history();
	else if (str_is_equal(cmd->value, "exit"))
		shell->run = false;
	else if (str_is_equal(cmd->value, "echo"))
		status = ft_echo(cmd);
	else if (str_is_equal(cmd->value, "pwd"))
		status = pwd();
	else if (str_is_equal(cmd->value, "clear"))
		status = ft_clear();
	else if (str_is_equal(cmd->value, "export"))
		status = ft_export(shell);
	else if (str_is_equal(cmd->value, "env"))
		status = ft_env(shell);
	else if (str_is_equal(cmd->value, "unset"))
		status = ft_unset();
	else if (str_is_equal(cmd->value, "cd"))
		status = ft_cd(cmd, shell);
	else
	{
		status = run_env_command(shell, cmd);
		if (status == CMD_FAILURE)
		{
			status = run_path_command(shell, cmd);
			if (status == CMD_FAILURE)
				print_invalid_cmd(cmd->value);
		}
	}
	*cmd->exit_status = status;
	return (status);
}
