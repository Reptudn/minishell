/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:07:19 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/16 16:28:29 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_shunting_node	*get_last_node(t_shunting_node *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

// frees one node
void	free_node(t_shunting_node *node)
{
	if (!node)
		return ;
	free(node->value);
	free(node->type);
	free(node->priority);
	free_split(node->args);
	free(node);
}

void	append_node(t_shunting_node *stack, t_shunting_node *node)
{
	if (!stack || !node)
		return ;
	while (stack->next)
		stack = stack->next;
	stack->next = node;
	node->prev = stack;
	node->next = NULL;
}

void	del_last_node(t_shunting_node **node_ptr)
{
	t_shunting_node	*node;
	t_shunting_node	*prev_node;

	if (!node_ptr || !*node_ptr)
		return ;
	prev_node = NULL;
	node = *node_ptr;
	while (node->next)
	{
		prev_node = node;
		node = node->next;
	}
	if (prev_node)
		prev_node->next = NULL;
	else
		*node_ptr = NULL;
	free_node(node);
}

// returns the first node from the input array and also removes it
// from the input array
t_shunting_node	*get_first_input(t_shunting_yard *yard)
{
	t_shunting_node	*node;

	if (!yard || !yard->input)
		return (NULL);
	node = yard->input;
	yard->input = yard->input->next;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
