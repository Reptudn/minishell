/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:56:52 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/11 09:49:26 by jkauker          ###   ########.fr       */
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
	if (*cmd1->exit_status == CMD_FAILURE)
		return (run_command(shell, cmd2));
	status = run_command(shell, cmd1);
	if (status == CMD_FAILURE)
		status = run_command(shell, cmd2);
	return (status);
}
