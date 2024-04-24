/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:36:47 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/24 18:30:50 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_shunting_node(t_shunting_node *node, int a)
{
	int	i;

	i = -1;
	if (!node)
	{
		printf("=> Total Nodes: %d\n", a);
		return ;
	}
	printf("-- Node: %d\n", a);
	printf("value: %s (%p)\n", node->value, node->value);
	printf("args:\n");
	if (node->args && node->args[0])
		while (node->args[++i] && node->args[0])
			printf("  %s\n", node->args[i]);
	else
		printf("  NULL\n");
	printf("Priority: %d\n", *node->priority);
	printf("----------\n");
	print_shunting_node(node->next, ++a);
}

void	print_all_stacks(t_shunting_yard *yard)
{
	printf("\n\n>>>>>>>>\nInput:\n");
	if (!yard->input)
		printf("  NULL\n");
	else
		print_shunting_node(yard->input, 0);
	printf("\nStack:\n");
	if (!yard->stack)
		printf("  NULL\n");
	else
		print_shunting_node(yard->stack, 0);
	printf("\nOutput:\n");
	if (!yard->output)
		printf("  NULL\n");
	else
		print_shunting_node(yard->output, 0);
}
