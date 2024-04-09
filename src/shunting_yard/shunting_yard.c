/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:03:13 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/08 08:39:11 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

int		get_operator_count(t_shunting_node *nodes);
int		get_command_count(t_shunting_node *nodes);
int		yard_len(t_shunting_node *stack);
void	print_shunting_node(t_shunting_node *node, int a);

t_shunting_node	*get_last_node(t_shunting_node *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
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

int	stack_to_output_end(t_shunting_yard *yard)
{
	t_shunting_node	*last_stack;
	t_shunting_node	*last_output;

	if (!yard || !yard->stack)
		return (0);
	if (get_last_node(yard->stack)
		&& *get_last_node(yard->stack)->type == OPEN_PAREN)
		return (0);
	last_stack = get_last_node(yard->stack);
	if (last_stack->prev)
		last_stack->prev->next = NULL;
	else
		yard->stack = NULL;
	if (yard->output)
	{
		last_output = get_last_node(yard->output);
		last_output->next = last_stack;
		last_stack->prev = last_output;
	}
	else
	{
		yard->output = last_stack;
		last_stack->prev = NULL;
	}
	last_stack->next = NULL;
	return (1);
}

void	place_node(t_shunting_node *node, t_shunting_yard *yard)
{
	t_shunting_node	*tmp;

	if (!node)
		return ;
	if (*node->type != NONE)
	{
		if (!yard->stack)
			yard->stack = node;
		else
		{
			tmp = get_last_node(yard->stack);
			while (tmp && *node->priority >= *tmp->priority)
			{
				stack_to_output_end(yard);
				tmp = get_last_node(yard->stack);
			}
			if (tmp)
				append_node(tmp, node);
			else
			{
				yard->stack = node;
				node->next = NULL;
				node->prev = NULL;
			}
		}
	}
	else
	{
		if (!yard->output)
			yard->output = node;
		else
			append_node(yard->output, node);
	}
}

// TODO: check if this is really doing the yard correctly
t_shunting_yard	*shunting_yard(char **tokens)
{
	t_shunting_yard	*yard;
	t_shunting_node	*node;

	yard = shunting_yard_create(tokens);
	if (!yard)
		return (NULL);
	if (get_operator_count(yard->input)
		!= get_command_count(yard->input) - 1)
	{
		printf("Unbalanced Commands and Operators\n");
		return (NULL);
	}
	while (yard->input)
	{
		node = get_first_input(yard);
		if (!node)
			break ;
		place_node(node, yard);
	}
	while (yard->stack)
		stack_to_output_end(yard);
	return (yard);
}
