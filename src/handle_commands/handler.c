/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:21:27 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/08 14:50:20 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void			yard_pop(t_shunting_node *node, t_shunting_yard *yard);
int				run_and(t_shell *shell, t_shunting_node *cmd1,
					t_shunting_node *cmd2);
int				run_or(t_shell *shell, t_shunting_node *cmd1,
					t_shunting_node *cmd2);
int				execute_cmd_chain(t_shell *shell, t_shunting_node *start,
					t_shunting_yard *yard);
int				get_command_count(t_shunting_node *nodes);
int				get_operator_count(t_shunting_node *nodes);
t_shunting_node	*get_operator_with_index(t_shunting_node *nodes, int index);

int	execution_manager(t_shunting_node *cmd1, t_shunting_node *cmd2,
	int operator, t_shell *shell)
{
	if (!cmd1 || !cmd2 || !shell)
		return (CMD_FAILURE);
	if (operator == OR && run_or(shell, cmd1, cmd2) == CMD_SUCCESS)
		return (CMD_SUCCESS);
	else if (operator == AND && run_and(shell, cmd1, cmd2) == CMD_SUCCESS)
		return (CMD_SUCCESS);
	return (CMD_FAILURE);
}

void	execute_commands_helper2(t_handler handler, t_shunting_node *cmd1,
		t_shunting_node *cmd2, t_shunting_yard *yard)
{
	if (handler.exit_status == -1)
	{
		handler.exit_status = execution_manager(cmd1, cmd2,
				*handler.operator->type, get_shell());
		yard_pop(handler.operator, yard);
		handler.operator = NULL;
		yard_pop(cmd1, yard);
		free(cmd2->value);
		cmd2->value = ft_strdup("echo");
		while (cmd2->args[++handler.i])
			free(cmd2->args[handler.i]);
		free(cmd2->args);
		cmd2->args = ft_split("-n", ' ');
		cmd2->update = 0;
		*cmd2->exit_status = handler.exit_status;
	}
}

int	execute_commands_helper(t_shunting_yard *yard, t_shell *shell,
		t_shunting_node *cmd1, t_shunting_node *cmd2)
{
	t_handler	handler;

	handler.index = -1;
	handler.i = -1;
	handler.operator_count = get_operator_count(yard->output);
	if (!yard || !yard->output || !shell)
		return (CMD_FAILURE);
	while (++handler.index < handler.operator_count && yard->output)
	{
		handler.operator = get_operator_with_index(yard->output, 1);
		if (!handler.operator && !yard->output->next && !yard->output->prev)
			break ;
		else if (!handler.operator)
			return (CMD_FAILURE);
		cmd2 = handler.operator->prev;
		if (!cmd2)
			return (CMD_FAILURE);
		cmd1 = cmd2->prev;
		if (!cmd1)
			return (CMD_FAILURE);
		handler.exit_status = execute_cmd_chain(shell, cmd1, yard);
		execute_commands_helper2(handler, cmd1, cmd2, yard);
	}
	return (handler.exit_status);
}

int	execute_commands(t_shunting_yard *yard, t_shell *shell)
{
	t_shunting_node	*cmd1;
	t_shunting_node	*cmd2;
	int				operator_count;
	int				exit_code;

	cmd1 = NULL;
	cmd2 = NULL;
	if (!yard || !yard->output || !shell)
		return (CMD_FAILURE);
	operator_count = get_operator_count(yard->output);
	if (operator_count == 0)
		return (run_command(shell, yard->output));
	if (operator_count != get_command_count(yard->output) - 1)
	{
		ft_putstr_fd("minishell: unbalanced tokens\n", 2);
		return (2);
	}
	exit_code = execute_commands_helper(yard, shell, cmd1, cmd2);
	if (exit_code != 0)
		*shell->exit_status = exit_code;
	else if (yard->output && !yard->output->next && !yard->output->prev)
		run_command(shell, yard->output);
	else
		printf("Last command error\n");
	return (exit_code);
}
