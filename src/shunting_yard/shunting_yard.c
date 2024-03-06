/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:03:13 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/06 17:48:01 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_shunting_node(t_shunting_node *node, int a);

// returns the first node from the input array and also removes it
// from the input array
t_shunting_node	*get_first_input(t_shunting_yard *yard)
{
	t_shunting_node	*node;

	node = yard->input;
	yard->input = yard->input->next;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	append_node(t_shunting_node *stack, t_shunting_node *node)
{
	while (stack->next)
		stack = stack->next;
	stack->next = node;
	node->prev = stack;
	node->next = NULL;
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

void	del_last_node(t_shunting_node *node)
{
	if (!node)
		return ;
	while (node->next)
		node = node->next;
	node->prev->next = NULL;
	free_node(node);
}

// return NULL if something fails else return a pointer to a t_shunting_yard
t_shunting_yard	*shunting_yard(char **tokens)
{
	t_shunting_yard	*yard;
	t_shunting_node	*node;

	yard = shunting_yard_create(tokens);
	if (!yard)
		return (NULL);
	while (yard->input)
	{
		node = get_first_input(yard);
		if (!node)
			break ;
		if (*node->type != NONE)
		{
			if (!yard->stack)
				yard->stack = node;
			else
				append_node(yard->stack, node);
		}
		else
		{
			if (!yard->output)
				yard->output = node;
			else
				append_node(yard->output, node);
		}
	}
	printf("\nInput:\n");
	print_shunting_node(yard->input, 0);
	printf("\nOutput:\n");
	print_shunting_node(yard->output, 0);
	printf("\nStack:\n");
	print_shunting_node(yard->stack, 0);
	return (yard);
}
