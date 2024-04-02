/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:56:52 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/02 10:39:16 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_or(t_shell *shell, t_shunting_node *cmd1, t_shunting_node *cmd2)
{
	int	status;

	if (!cmd1 || !cmd2 || !shell)
		return (CMD_FAILURE);
	if (*cmd1->exit_status == CMD_SUCCESS)
		return (CMD_SUCCESS);
	if (*cmd1->exit_status > CMD_SUCCESS)
		return (run_command(shell, cmd2));
	status = run_command(shell, cmd1);
	if (status > CMD_SUCCESS)
		status = run_command(shell, cmd2);
	return (status);
}
