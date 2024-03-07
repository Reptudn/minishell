/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:03:13 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/07 00:10:33 by jkauker          ###   ########.fr       */
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

void	del_last_node(t_shunting_node **node_ptr)
{
	t_shunting_node	*node;
	t_shunting_node	*prev_node;

	if (!node_ptr || !*node_ptr)
		return;
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
	t_shunting_node	*tmp;

	if (!node)
		return ;
	printf("placing node: %c\n", node->value[0]);
	if (*node->type == OPEN_PAREN)
	{
		if (!yard->stack)
			yard->stack = node;
		else
			append_node(yard->stack, node);
	}
	else if (*node->type == CLOSE_PAREN) // it never gets inside this block
	{
		while (yard->stack && *yard->stack->type != OPEN_PAREN)
			stack_to_output_end(yard);
		if (!yard->stack)
			printf("Error: Unbalanced parenthesis\n");
		else if (yard->stack && *yard->stack->type == OPEN_PAREN)
		{
			printf("found open paren in stack\n");
			// del_last_node(&yard->stack);
			if (!yard->stack->prev)
			{
				yard->stack = NULL;
				printf("stack is null\n");
			}
			else
			{
				tmp = yard->stack;
				while (tmp->next)
					tmp = tmp->next;
				printf("end of stack: %s\n", tmp->value);
				tmp->prev->next = NULL;
				// unsafe af cuz the struct is flying around somewhere malloced
			};
		}
	}
	else if (*node->type != NONE)
	{
		if (!yard->stack)
			yard->stack = node;
		else
		{
			tmp = yard->stack;
			while (tmp->next)
				tmp = tmp->next;
			while (tmp && *node->priority >= *tmp->priority) {
				stack_to_output_end(yard);
				tmp = yard->stack;
				while (tmp && tmp->next)
					tmp = tmp->next;
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

// return NULL if something fails else return a pointer to a t_shunting_yard
t_shunting_yard	*shunting_yard(char **tokens)
{
	t_shunting_yard	*yard;
	t_shunting_node	*node;

	yard = shunting_yard_create(tokens);
	if (!yard)
		return (NULL);
	print_all_stacks(yard);
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
