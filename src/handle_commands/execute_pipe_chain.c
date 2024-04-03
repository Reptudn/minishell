/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_chain.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:21:25 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/03 12:24:47 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	return (node);
}

t_shunting_node	**get_cmd_chain(t_shunting_node *start, int *len, int *type)
{
	t_shunting_node	**chain;
	t_shunting_node	*node;
	t_shunting_node	*last;
	int				i;

	if (*start->type == NONE)
		return (NULL);
	*type = *start->type;
	*len = 0;
	node = start;
	last = get_last_opeartor(start, *type);
	while (node && node != last)
	{
		if (*node->type != *type)
			*len += 1;
		node = node->next;
	}
	chain = (t_shunting_node **)malloc(sizeof(t_shunting_node *) * (*len + 1));
	if (!chain)
		return (NULL);
	chain[*len] = NULL;
	node = start;
	i = -1;
	while (node && *node->type == *type)
	{
		chain[++i] = node;
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
	while (++i < len && chain[i])
		printf("chain[%d]: %s\n", i, chain[i]->value);
}

int execute_cmd_chain(t_shell *shell, t_shunting_node *start, t_shunting_yard *yard)
{
	t_shunting_node	**chain;
	int				len;
	int				type;
	int				status;
	char			*out;

	chain = get_cmd_chain(start, &len, &type);
	if (!chain)
		return (CMD_FAILURE);
	print_cmd_chain(chain, len);
	exit(0);
	if (type == PIPE)
	{
		printf("PIPE\n");
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
	pop_cmd_chain(chain, yard, len);
	free(chain);
	return (CMD_SUCCESS);
}
