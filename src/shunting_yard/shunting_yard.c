/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:03:13 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/06 21:07:01 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

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
	if (!stack || !node)
		return ;
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

void	stack_to_output_end(t_shunting_yard *yard)
{
	t_shunting_node	*last_stack;
	t_shunting_node	*last_output;
	t_shunting_node	*tmp;

	if (!yard || !yard->stack)
		return ;
	last_stack = yard->stack;
	while (last_stack->next)
		last_stack = last_stack->next;
	if (last_stack->prev)
		last_stack->prev->next = NULL;
	else
		yard->stack = NULL;
	if (yard->output)
	{
		last_output = yard->output;
		while (last_output->next)
			last_output = last_output->next;
		last_output->next = last_stack;
		last_stack->prev = last_output;
	}
	else
	{
		yard->output = last_stack;
		last_stack->prev = NULL;
	}
	last_stack->next = NULL;
}

void	place_node(t_shunting_node *node, t_shunting_yard *yard)
{
	if (!node)
		return ;
	printf("Placing node ");
	if (*node->type != NONE)
	{
		if (!yard->stack)
			yard->stack = node;
		else
			append_node(yard->stack, node);
		printf("in stack\t:  %s\n", node->value);
	}
	else
	{
		if (!yard->output)
			yard->output = node;
		else
			append_node(yard->output, node);
		printf("in output\t:  %s\n", node->value);
	}
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
		place_node(node, yard);
	}
	while (yard->stack)
		stack_to_output_end(yard);
	print_all_stacks(yard);
	return (yard);
}
