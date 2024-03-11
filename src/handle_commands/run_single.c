/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_single.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:27:22 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/11 10:32:54 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_command(t_shell *shell, t_shunting_node *cmd)
{
	int	status;

	printf("run_command\n");
	if (!cmd || !shell)
		return (CMD_FAILURE);
	printf("run_command2\n");
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
