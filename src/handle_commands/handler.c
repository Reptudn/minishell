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

void	yard_pop(t_shunting_node *node, t_shunting_yard *yard);

int		run_and(t_shell *shell, t_shunting_node *cmd1, t_shunting_node *cmd2);
int		run_or(t_shell *shell, t_shunting_node *cmd1, t_shunting_node *cmd2);
char	*run_pipe(t_shell *shell, t_shunting_node **chain, int counter,
			int pipe_amount, char *str);
int		redirect_in(t_shunting_node *cmd, t_shunting_node *cmd2,
			t_shell *shell);
int		redirect_out(t_shell *shell, t_shunting_node *cmd,
			t_shunting_node *cmd2, int in_fd);
int		run_append(t_shell *shell, t_shunting_node *cmd1,
			t_shunting_node *cmd2);
int		run_delimiter(t_shunting_node **chain, t_shell *shell);

int		execute_cmd_chain(t_shell *shell, t_shunting_node *start,
			t_shunting_yard *yard);

int		get_command_count(t_shunting_node *nodes);

int	get_operator_count(t_shunting_node *nodes)
{
	int	count;

	count = 0;
	while (nodes)
	{
		count++;
		if (*nodes->type == NONE || *nodes->type == OPEN_PAREN
			|| *nodes->type == CLOSE_PAREN)
			count--;
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
	return (CMD_FAILURE);
}

int	execute_commands_helper(t_shunting_yard *yard, t_shell *shell,
		t_shunting_node *cmd1, t_shunting_node *cmd2)
{
	int				index;
	int				operator_count;
	int				exit_status;
	t_shunting_node	*operator;

	index = -1;
	operator_count = get_operator_count(yard->output);
	while (++index < operator_count && yard->output)
	{
		operator = get_operator_with_index(yard->output, 1);
		if (!operator && !yard->output->next && !yard->output->prev)
			break ;
		else if (!operator)
			return (CMD_FAILURE);
		cmd2 = operator->prev;
		if (!cmd2)
			return (CMD_FAILURE);
		cmd1 = cmd2->prev;
		if (!cmd1)
			return (CMD_FAILURE);
		if (execute_cmd_chain(shell, cmd1, yard) == -1)
		{
			exit_status = execution_manager(cmd1, cmd2, *operator->type, shell);
			yard_pop(operator, yard);
			yard_pop(cmd1, yard);
			cmd2->value = ft_strdup("echo");
			cmd2->args = ft_split("-n", ' ');
			cmd2->update = 0;
			*cmd2->exit_status = exit_status;
		}
	}
	return (exit_status);
}

int	execute_commands(t_shunting_yard *yard, t_shell *shell)
{
	t_shunting_node	*cmd1;
	t_shunting_node	*cmd2;
	int				operator_count;
	int				exit_status;

	exit_status = CMD_FAILURE;
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
		return (CMD_FAILURE);
	}
	execute_commands_helper(yard, shell, cmd1, cmd2);
	if (yard->output && !yard->output->next && !yard->output->prev)
		exit_status = run_command(shell, yard->output);
	else
		printf("Last command error\n");
	return (exit_status);
}
