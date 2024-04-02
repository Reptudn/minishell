/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:21:27 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/27 15:53:24 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	yard_pop(t_shunting_node *node, t_shunting_yard *yard);

int		run_and(t_shell *shell, t_shunting_node *cmd1, t_shunting_node *cmd2);
int		run_or(t_shell *shell, t_shunting_node *cmd1, t_shunting_node *cmd2);
int		run_pipe_cmd(t_shunting_node *cmd1, t_shunting_node *cmd2,
			t_shell *shell);
int		redirect_in(t_shunting_node *cmd,
			t_shunting_node *cmd2, t_shell *shell);
int		redirect_out(t_shunting_node *cmd, t_shunting_node *cmd2);
int		run_append(t_shell *shell, t_shunting_node *cmd1,
			t_shunting_node *cmd2);
int		run_delimiter(t_shell *shell, t_shunting_node *cmd1,
			t_shunting_node *cmd2);

void	replace_variable(char **args, t_shell *shell, int status);

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
	if (index < 1 || index > get_operator_count(nodes))
		return (NULL);
	while (nodes)
	{
		if (*nodes->type != NONE)
		{
			if (index == 1)
				return (nodes);
			index--;
		}
		nodes = nodes->next;
	}
	return (NULL);
}

int	execution_manager(t_shunting_node *cmd1, t_shunting_node *cmd2,
	int operator, t_shell *shell)
{
	if (!cmd1 || !cmd2 || !shell)
		return (CMD_FAILURE);
	if (operator == OR && run_or(shell, cmd1, cmd2) == CMD_SUCCESS)
		return (CMD_SUCCESS);
	else if (operator == AND && run_and(shell, cmd1, cmd2) == CMD_SUCCESS)
		return (CMD_SUCCESS);
	else if (operator == PIPE && run_pipe_cmd(cmd1, cmd2, shell) == CMD_SUCCESS)
		return (CMD_SUCCESS);
	else if (operator == REDIRECT_IN
		&& redirect_in(cmd1, cmd2, shell) == CMD_SUCCESS)
		return (CMD_SUCCESS);
	else if (operator == REDIRECT_OUT
		&& redirect_out(cmd1, cmd2) == CMD_SUCCESS)
		return (CMD_SUCCESS);
	else if (operator == REDIRECT_OUT_APPEND
		&& run_append(shell, cmd1, cmd2) == CMD_SUCCESS)
		return (CMD_SUCCESS);
	else if (operator == REDIRECT_IN_DELIMITER
		&& run_delimiter(shell, cmd1, cmd2) == CMD_SUCCESS)
		return (CMD_SUCCESS);
	return (CMD_FAILURE);
}

int	execute_commands(t_shunting_yard *yard, t_shell *shell, int status)
{
	t_shunting_node	*operator;
	t_shunting_node	*cmd1;
	t_shunting_node	*cmd2;
	int				operator_count;
	int				index;
	int				exit_status;

	index = -1;
	if (!yard || !yard->output || !shell)
		return (CMD_FAILURE);
	operator_count = get_operator_count(yard->output);
	if (operator_count == 0)
	{
		replace_variable(yard->output->args, shell, status);
		return (run_command(shell, yard->output));
	}
	if (operator_count != get_command_count(yard->output) - 1)
	{
		printf("Invalid operator count\n");
		return (CMD_FAILURE);
	}
	// print_all_stacks(yard);
	while (++index < operator_count && yard->output) // TODO: fix this that it works correctly
	{
		operator = get_operator_with_index(yard->output, 1);
		if (!operator)
			return (CMD_FAILURE);
		cmd2 = operator->prev;
		if (!cmd2)
			return (CMD_FAILURE);
		cmd1 = cmd2->prev;
		if (!cmd1)
			return (CMD_FAILURE);
		replace_variable(cmd1->args, shell, status);
		replace_variable(cmd2->args, shell, status);
		exit_status = execution_manager(cmd1, cmd2, *operator->type, shell);
		// if (exit_status > CMD_SUCCESS)
		// 	return (exit_status);
		cmd1->args = ft_split("-n <OUTPUT FROM LAST TWO COMMANDS HERE>", ' ');
		cmd1->value = ft_strdup("echo");
		cmd1->type = malloc(sizeof(int));
		*cmd1->type = NONE;
		yard_pop(operator, yard);
		yard_pop(cmd2, yard);

	}
	return (exit_status);
}

// echo hi && echo hello || echo world && echo bye