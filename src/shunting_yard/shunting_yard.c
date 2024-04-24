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

int				get_operator_count(t_shunting_node *nodes);
int				get_command_count(t_shunting_node *nodes);
int				yard_len(t_shunting_node *stack);
void			print_shunting_node(t_shunting_node *node, int a);
t_shunting_node	*get_last_node(t_shunting_node *node);
void			free_node(t_shunting_node *node);
void			del_last_node(t_shunting_node **node_ptr);
void			append_node(t_shunting_node *stack, t_shunting_node *node);
t_shunting_node	*get_first_input(t_shunting_yard *yard);
void			place_node(t_shunting_node *node, t_shunting_yard *yard);

t_shunting_node	*remove_last_from_stack(t_shunting_yard *yard)
{
	t_shunting_node	*last_stack;

	if (!yard || !yard->stack)
		return (NULL);
	if (get_last_node(yard->stack)
		&& *get_last_node(yard->stack)->type == OPEN_PAREN)
		return (NULL);
	last_stack = get_last_node(yard->stack);
	if (last_stack->prev)
		last_stack->prev->next = NULL;
	else
		yard->stack = NULL;
	return (last_stack);
}

int	add_to_output(t_shunting_yard *yard, t_shunting_node *node)
{
	t_shunting_node	*last_output;

	if (!node)
		return (0);
	if (yard->output)
	{
		last_output = get_last_node(yard->output);
		last_output->next = node;
		node->prev = last_output;
	}
	else
	{
		yard->output = node;
		node->prev = NULL;
	}
	node->next = NULL;
	return (1);
}

int	stack_to_output_end(t_shunting_yard *yard)
{
	t_shunting_node	*node;

	node = remove_last_from_stack(yard);
	return (add_to_output(yard, node));
}

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
		ft_putstr_fd("Unbalanced Commands and Operators\n", STDERR_FILENO);
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
	print_all_stacks(yard);
	return (yard);
}
