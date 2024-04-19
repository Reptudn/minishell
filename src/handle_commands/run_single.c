/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_single.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:27:22 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 13:37:10 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_builtin_command(t_shell *shell, t_shunting_node *cmd)
{
	if (str_is_equal(cmd->value, "history"))
		return (display_history());
	else if (str_is_equal(cmd->value, "exit"))
		return (ft_exit(shell, cmd));
	else if (str_is_equal(cmd->value, "echo"))
		return (ft_echo(cmd));
	else if (str_is_equal(cmd->value, "pwd"))
		return (pwd());
	else if (str_is_equal(cmd->value, "clear"))
		return (ft_clear());
	else if (str_is_equal(cmd->value, "export"))
		return (ft_export(shell, cmd));
	else if (str_is_equal(cmd->value, "env"))
		return (ft_env(shell));
	else if (str_is_equal(cmd->value, "unset"))
		return (ft_unset(cmd, shell));
	else if (str_is_equal(cmd->value, "cd"))
		return (ft_cd(cmd, shell));
	else
		return (-1);
}

int	run_external_command(t_shell *shell, t_shunting_node *cmd)
{
	int	status;

	status = run_env_command(shell, cmd);
	if (status == CMD_FAILURE)
	{
		status = run_path_command(shell, cmd);
		if (status == CMD_FAILURE)
		{
			print_invalid_cmd(cmd->value, "FAILURE", CMD_NOT_FOUND);
			status = CMD_NOT_FOUND;
		}
		else if (status == CMD_IMPROP)
			print_invalid_cmd(cmd->value, "IMPROP", CMD_IMPROP);
	}
	return (status);
}

int	run_command(t_shell *shell, t_shunting_node *cmd)
{
	int	status;

	if (!cmd || !shell)
		return (CMD_FAILURE);
	replace_variable(cmd->args, shell); // TODO: not just the args have to be replaced but also the value
	status = run_builtin_command(shell, cmd);
	if (status == -1)
		status = run_external_command(shell, cmd);
	if (cmd->exit_status == NULL)
		cmd->exit_status = malloc(sizeof(int));
	if (!cmd->update)
		return (status);
	*cmd->exit_status = status;
	*shell->exit_status = status;
	return (status);
}
