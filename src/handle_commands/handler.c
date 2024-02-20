/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:21:27 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/20 12:28:06 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_and(t_shell *shell, t_command *cmd1, t_command *cmd2);
int	run_or(t_shell *shell, t_command *cmd1, t_command *cmd2);
int	run_pipe_cmd(t_command *cmd1, t_command *cmd2, t_shell *shell);

int	execute_commands(t_shell *shell, t_command *cmd1, t_command *cmd2)
{
	if (!cmd1 || (!cmd1 && !cmd2))
		return (CMD_SUCCESS);
	// if ((*cmd1->operator_type != NONE) && !cmd2) // this gives a segv probably when cmd2 is NULL
	// {
	// 	printf("syntax error near unexpected token\n");
	// 	return (CMD_FAILURE);
	// }
	if (!cmd2)
		return (run_command(shell, cmd1));
	else if (*cmd1->operator_type == OR && run_or(shell, cmd1, cmd2))
		return (CMD_FAILURE);
	else if (*cmd1->operator_type == AND && run_and(shell, cmd1, cmd2))
		return (CMD_FAILURE);
	else if (*cmd1->operator_type == PIPE && run_pipe_cmd(cmd1, cmd2, shell))
		return (CMD_FAILURE);
	return (execute_commands(shell, cmd2, cmd2->next));
}
