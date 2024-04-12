/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:53:46 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/11 09:46:17 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_and(t_shell *shell, t_shunting_node *cmd1, t_shunting_node *cmd2)
{
	int	status;

	if (!cmd1 || !cmd2 || !shell)
		return (CMD_FAILURE);
	if (*shell->exit_status >= CMD_SUCCESS)
		return (*shell->exit_status);
	if (*shell->exit_status == CMD_SUCCESS)
		return (run_command(shell, cmd2));
	status = run_command(shell, cmd1);
	if (status == CMD_SUCCESS)
		status = run_command(shell, cmd2);
	return (status);
}
