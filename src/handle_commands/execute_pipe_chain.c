/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_chain.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:21:25 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 09:47:32 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	yard_pop(t_shunting_node *pop, t_shunting_yard *yard);

t_shunting_node	*get_last_opeartor(t_shunting_node *node, int type)
{
	t_shunting_node	*last;

	while (node)
	{
		if (*node->type == type)
			last = node;
		else if (*node->type != type && *node->type != NONE)
			return (last);
		node = node->next;
	}
	return (last);
}

// TODO it is not correctly adding the pointers in the chain
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
	printf("type: %d\n", *type);
	node = start;
	last = get_last_opeartor(node, *type);
	printf("start: %s\n", start->value);
	printf("last: %s\n", last ? last->value : "NULL");
	int l = 0;
	while (node && node->prev != last && node->next)
	{
		if (*node->type == *type)
			*len += 1;
		node = node->next;
		printf("l: %d", l++);
	}
	while (node && node->prev)
		node = node->prev;
	*len += 1;
	printf("len: %d\n", *len);
	printf("start: %s\n", start->value);
	chain = (t_shunting_node **)malloc(sizeof(t_shunting_node *) * (*len + 1));
	if (!chain)
		return (NULL);
	chain[*len] = NULL;
	printf("start: %s\n", start->value);
	i = -1;
	while (node && node->prev != last)
	{
		printf("Node is %s\n", node->value);
		if (*node->type != *type && *node->type == NONE)
		{
			chain[++i] = node;
			printf(" added chain[%d]: %s\n", i, node->value);
		}
		else printf("skipped: %s\n", node->value);
		node = node->next;
	}
	return (chain);
}

// after calling this the first one of the chain can still be used as echo and save
// the output there
void	pop_cmd_chain(t_shunting_yard *yard, t_shunting_node **chain, int len)
{
	while (len-- > 1)
		yard_pop(chain[len], yard);
}

void	print_cmd_chain(t_shunting_node **chain, int len)
{
	int	i;

	i = -1;
	printf("Command Chain:\n");
	if (!chain)
	{
		printf("  No chain\n");
		return ;
	}
	while (++i < len && chain[i])
		printf("chain[%d]: %s\n", i, (chain[i])->value);
}

int execute_cmd_chain(t_shell *shell, t_shunting_node *start, t_shunting_yard *yard)
{
	t_shunting_node	**chain;
	int				len;
	int				type;
	// int				status;
	// char			*out;

	(void)shell;
	chain = get_cmd_chain(start, &len, &type);
	printf("pipe chain made function returned");
	print_cmd_chain(chain, len);
	if (!chain)
		return (CMD_FAILURE);
	if (type == PIPE)
	{
		printf("-> PIPE\n");
	}
	else if (type == REDIRECT_IN)
	{
		printf("REDIRECT_IN\n");
	}
	else if (type == REDIRECT_OUT)
	{
		printf("REDIRECT_OUT\n");
	}
	else if (type == REDIRECT_OUT_APPEND)
	{
		printf("APPEND\n");
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
	pop_cmd_chain(yard, chain, len);
	free(chain);
	exit(0);
	return (CMD_SUCCESS);
}
