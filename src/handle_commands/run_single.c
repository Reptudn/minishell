/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_single.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:27:22 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/20 09:32:39 by jkauker          ###   ########.fr       */
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
		status = ft_export(shell, cmd);
	else if (str_is_equal(cmd->value, "env"))
		status = ft_env(shell);
	else if (str_is_equal(cmd->value, "unset"))
		status = ft_unset(cmd, shell);
	else if (str_is_equal(cmd->value, "cd"))
		status = ft_cd(cmd, shell);
	else
	{
		status = run_env_command(shell, cmd);
		if (status == CMD_FAILURE)
		{
			status = run_path_command(shell, cmd);
			if (status == CMD_FAILURE)
			{
				print_invalid_cmd(cmd->value);
				status = CMD_NOT_FOUND;
			}
			else if (status == CMD_IMPROP)
				printf("%sminishell: No permission\n%s",
					COLOR_RED, COLOR_RESET);
		}
	}
	*cmd->exit_status = status;
	return (status);
}
