/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_chain.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:21:25 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/08 09:18:43 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	yard_pop(t_shunting_node *node, t_shunting_yard *yard);

int		run_and(t_shell *shell, t_shunting_node *cmd1, t_shunting_node *cmd2);
int		run_or(t_shell *shell, t_shunting_node *cmd1, t_shunting_node *cmd2);
char	*run_pipe(t_shell *shell, t_shunting_node **chain, int counter, int pipe_amount, char *str);
int		redirect_in(t_shunting_node *cmd, t_shunting_node *cmd2, t_shell *shell);
int		redirect_out(t_shell *shell, t_shunting_node **chain, int redirection_amout);
int		run_append(t_shell *shell, t_shunting_node **chain, int append_amount);
int		run_delimiter(t_shell *shell, t_shunting_node *cmd1,
			t_shunting_node *cmd2);

void	replace_variable(char **args, t_shell *shell, int status);

void	yard_pop(t_shunting_node *pop, t_shunting_yard *yard);

t_shunting_node	*get_last_opeartor(t_shunting_node *node, int type)
{
	t_shunting_node	*last;

	last = NULL;
	while (node && node != last && node->next
		&& (*node->type == type || *node->type == NONE))
	{
		// if the last node is the operator we want and the current and next are both Commands (NONE Type) we know there was an AND or OR inbetween
		if (node->prev && *node->prev->type == type && *node->type == NONE
			&& node->next && *node->next->type == NONE)
			break ;
		if (*node->type == type)
			last = node;
		node = node->next;
	}
	return (last);
}

t_shunting_node	**get_cmd_chain(t_shunting_node *start, int *len, int *type)
{
	t_shunting_node	**chain;
	t_shunting_node	*node;
	t_shunting_node	*last;
	int				i;

	if (!start)
		return (NULL);
	node = start;
	while (node && *node->type == NONE)
		node = node->next;
	*type = *node->type;
	*len = 0;
	node = start;
	last = get_last_opeartor(node, *type);
	printf("last: %s\n", last->value);
	while (node && node != last && node->next
		&& (*node->type == *type || *node->type == NONE))
	{
		if (*node->type != *type)
			*len += 1;
		node = node->next;
	}
	chain = (t_shunting_node **)malloc(sizeof(t_shunting_node *) * (*len + 1));
	if (!chain)
		return (NULL);
	chain[*len] = NULL;
	i = -1;
	while (start && start != last && start->next
		&& (*start->type == *type || *start->type == NONE))
	{
		if (*start->type != *type && *start->type == NONE)
			chain[++i] = start;
		start = start->next;
	}
	return (chain);
}

// after calling this the first one of the chain can still be used as echo and save
// the output there
void	pop_cmd_chain(t_shunting_yard *yard, t_shunting_node **chain, int len)
{
	if (!chain)
		return ;
	while (len-- > 1)
		yard_pop(chain[len], yard);
}

void	print_cmd_chain(t_shunting_node **chain)
{
	int	i;

	i = -1;
	printf("Command Chain:\n");
	if (!chain)
	{
		printf("  No chain\n");
		return ;
	}
	while (chain[++i])
		printf("  chain[%d]: %s\n", i, (chain[i])->value);
}

// TODO: check funcitons for success and failure
int execute_cmd_chain(t_shell *shell, t_shunting_node *start, t_shunting_yard *yard, int *status)
{
	t_shunting_node	**chain;
	int				len;
	int				type;
	int				i;
	char			*out;

	static int chain_count = 0;
	printf("Chain count: %d\n", chain_count++);
	print_all_stacks(yard);
	out = ft_strdup("");
	chain = get_cmd_chain(start, &len, &type);
	i = -1;
	print_cmd_chain(chain);
	if (!chain)
		return (CMD_FAILURE);
	while (++i < len && chain[i])
		replace_variable(chain[i]->args, shell, *status);
	if (type == PIPE)
	{
		(*chain)->args = ft_split(run_pipe(shell, chain, 0, len, out), ' ');
	}
	else if (type == REDIRECT_IN)
	{
		printf("REDIRECT_IN\n");
	}
	else if (type == REDIRECT_OUT)
	{
		redirect_out(shell, chain, len);
		(*chain)->args = ft_split("-n  ", ' ');
	}
	else if (type == REDIRECT_OUT_APPEND)
	{
		run_append(shell, chain, len);
		(*chain)->args = ft_split("-n  ", ' ');
	}
	else if (type == REDIRECT_IN_DELIMITER)
	{
		printf("DELIMITER\n");
	}
	else
	{
		printf("no chain needed\n");
		pop_cmd_chain(yard, chain, len);
		yard_pop(*chain, yard);
		free(chain);
	}
	(*chain)->value = ft_strdup("echo");
	pop_cmd_chain(yard, chain, len);
	free(chain);
	return (CMD_SUCCESS);
}
