/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_chain_helper.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:49:59 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/06 14:04:12 by jkauker          ###   ########.fr       */
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
