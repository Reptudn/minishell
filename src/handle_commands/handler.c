/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:21:27 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/11 10:34:49 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_and(t_shell *shell, t_shunting_node *cmd1, t_shunting_node *cmd2);
int	run_or(t_shell *shell, t_shunting_node *cmd1, t_shunting_node *cmd2);
int	run_pipe_cmd(t_shunting_node *cmd1, t_shunting_node *cmd2, t_shell *shell);
int	redirect_in(t_shunting_node *cmd, t_shell *shell);
int	redirect_out(t_shunting_node *cmd, t_shell *shell);

// int	execute_commands(t_shell *shell, t_command *cmd1, t_command *cmd2)
// {
// 	if (!cmd1 || (!cmd1 && !cmd2))
// 		return (CMD_SUCCESS);
// 	if (!cmd2)
// 		return (run_command(shell, cmd1));
// 	else if (*cmd1->operator_type == OR && run_or(shell, cmd1, cmd2))
// 		return (CMD_FAILURE);
// 	else if (*cmd1->operator_type == AND && run_and(shell, cmd1, cmd2))
// 		return (CMD_FAILURE);
// 	else if (*cmd1->operator_type == PIPE && run_pipe_cmd(cmd1, cmd2, shell))
// 		return (CMD_FAILURE);
// 	else if (*cmd1->operator_type == REDIRECT_IN && redirect_in(cmd1, shell))
// 		return (CMD_FAILURE);
// 	else if (*cmd1->operator_type == REDIRECT_OUT && redirect_out(cmd1, shell))
// 		return (CMD_FAILURE);
// 	return (execute_commands(shell, cmd2, cmd2->next));
// }

int	get_operator_count(t_shunting_node *nodes)
{
	int	count;

	count = 0;
	while (nodes)
	{
		if (*nodes->type != NONE)
			count++;
		nodes = nodes->next;
	}
	return (count);
}
int	get_command_count(t_shunting_node *nodes)
{
	int	count;

	count = 0;
	while (nodes)
	{
		if (*nodes->type == NONE)
			count++;
		nodes = nodes->next;
	}
	return (count);
}

t_shunting_node	*get_operator_with_index(t_shunting_node *nodes, int index)
{
	int	total;

	total = get_operator_count(nodes);
	if (index < 0 || index >= total)
		return (NULL);
	while (nodes)
	{
		if (*nodes->type != NONE)
		{
			if (!index)
				return (nodes);
			index--;
		}
		nodes = nodes->next;
	}
	return (NULL);
}

int	execution_manager(t_shunting_node *cmd1, t_shunting_node *cmd2, int operator,
	t_shell *shell)
{
	if (!cmd1 || !cmd2 || !shell)
		return (CMD_FAILURE);
	if (operator == OR && run_or(shell, cmd1, cmd2))
		return (CMD_FAILURE);
	else if (operator == AND && run_and(shell, cmd1, cmd2))
		return (CMD_FAILURE);
	else if (operator == PIPE && run_pipe_cmd(cmd1, cmd2, shell))
		return (CMD_FAILURE);
	else if (operator == REDIRECT_IN && redirect_in(cmd1, shell))
		return (CMD_FAILURE);
	else if (operator == REDIRECT_OUT && redirect_out(cmd1, shell))
		return (CMD_FAILURE);
	return (CMD_SUCCESS);
}

int	execute_commands(t_shunting_yard *yard, t_shell *shell)
{
	t_shunting_node	*operator;
	t_shunting_node	*cmd1;
	t_shunting_node	*cmd2;
	int				operator_count;
	int				index;

	printf("Executing commands\n");
	index = -1;
	if (!yard || !yard->output || !shell)
		return (CMD_FAILURE);
	operator_count = get_operator_count(yard->output);
	printf("Operator count: %d\n", operator_count);
	if (operator_count == 0)
		return (run_command(shell, yard->output));
	if (operator_count != get_command_count(yard->output) - 1)
	{
		printf("Invalid operator count\n");
		return (CMD_FAILURE);
	}
	while (++index < operator_count) // this aint working yet
	{
		printf("Try executing (%d)\n", index);
		operator = get_operator_with_index(yard->output, index);
		if (!operator)
			return (CMD_FAILURE);
		cmd1 = operator->prev;
		if (!cmd1)
			return (CMD_FAILURE);
		cmd2 = cmd1->prev;
		if (!cmd2)
			return (CMD_FAILURE);
		if (!execution_manager(cmd1, cmd2, *operator->type, shell))
			return (CMD_FAILURE);
	}
	// free_shunting_yard(yard);
	return (CMD_SUCCESS);
}
