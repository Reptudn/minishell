/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:36:01 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/14 12:19:21 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void			append_node(t_shunting_node *stack, t_shunting_node *node);
t_shunting_node	*get_last_node(t_shunting_node *node);
int				stack_to_output_end(t_shunting_yard *yard);

void	place_operator_node(t_shunting_node *node, t_shunting_yard *yard)
{
	t_shunting_node	*tmp;

	if (!yard->stack)
		yard->stack = node;
	else
	{
		tmp = get_last_node(yard->stack);
		while (tmp && *node->priority <= *tmp->priority) // TODO: this causes endless loop when chaining commands
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

void	place_operand_node(t_shunting_node *node, t_shunting_yard *yard)
{
	if (!yard->output)
		yard->output = node;
	else
		append_node(yard->output, node);
}

void	place_node(t_shunting_node *node, t_shunting_yard *yard)
{
	if (!node)
		return ;
	if (*node->type != NONE)
		place_operator_node(node, yard);
	else
		place_operand_node(node, yard);
}
