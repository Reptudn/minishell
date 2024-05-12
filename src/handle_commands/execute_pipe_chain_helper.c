/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_chain_helper.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:49:59 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/12 15:31:37 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	yard_pop(t_shunting_node *pop, t_shunting_yard *yard);

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

void	pop_cmd_chain(t_shunting_yard *yard, t_shunting_node **chain,
		int len, int type)
{
	if (!chain)
		return ;
	while (--len > 0)
	{
		if (chain[len]->next && *chain[len]->next->type == type)
			yard_pop(chain[len]->next, yard);
		if (chain[len]->prev && *chain[len]->prev->type == type)
			yard_pop(chain[len]->prev, yard);
		yard_pop(chain[len], yard);
	}
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

t_shunting_node	*get_last_opeartor(t_shunting_node *node, int type)
{
	t_shunting_node	*last;
	t_shunting_node	*start;

	last = NULL;
	start = node;
	while (node && node != last && node->next
		&& (*node->type == type || *node->type == NONE))
	{
		if (node != start && node->prev && *node->prev->type == type
			&& *node->type == NONE && node->next && *node->next->type == NONE)
			break ;
		if (*node->type == type)
			last = node;
		node = node->next;
	}
	if (node && *node->type == type)
		last = node;
	return (last);
}

t_shunting_node	**fill_chain(t_shunting_node *start, t_shunting_node *last,
		int *len, int type)
{
	t_shunting_node	**chain;
	int				i;

	chain = (t_shunting_node **)malloc(sizeof(t_shunting_node *) * (*len + 1));
	if (!chain)
		return (NULL);
	chain[*len] = NULL;
	i = -1;
	while (start && start != last && start->next
		&& (*start->type == type || *start->type == NONE))
	{
		if (*start->type != type && *start->type == NONE)
			chain[++i] = start;
		start = start->next;
	}
	return (chain);
}
