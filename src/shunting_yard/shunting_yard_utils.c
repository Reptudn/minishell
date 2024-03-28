/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:40:50 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/28 14:57:13 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_operator_priority(char *operator);

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
	printf("value: %s\n", node->value);
	printf("args:\n");
	if (node->args && node->args[0])
		while (node->args[++i] && node->args[0])
			printf("  %s\n", node->args[i]);
	else
		printf("  NULL\n");
	if (node->type)
		printf("type: %d\n", *node->type);
	else
		printf("type: -1\n");
	if (node->priority)
		printf("priority: %d\n", *node->priority);
	else
		printf("priority: -1\n");
	printf("----------\n");
	print_shunting_node(node->next, ++a);
}

t_shunting_node	*shunting_node_new(char	**tokens, int *step)
{
	t_shunting_node	*node;
	int				i;

	if (!tokens || !*tokens)
		return (NULL);
	node = (t_shunting_node *)malloc(sizeof(t_shunting_node));
	if (!node)
		return (NULL);
	node->type = malloc(sizeof(int));
	node->priority = malloc(sizeof(int));
	node->fd = malloc(sizeof(int));
	node->exit_status = malloc(sizeof(int));
	*node->fd = 1;
	*node->exit_status = -1;
	*node->type = is_operator(tokens[0]);
	*node->priority = get_operator_priority(tokens[0]);
	if (is_operator(tokens[0]) != NONE)
	{
		node->value = ft_strdup(tokens[0]);
		node->args = NULL;
		node->next = NULL;
		node->prev = NULL;
		*step += 1;
		return (node);
	}
	i = -1;
	node->value = ft_strdup(tokens[++i]);
	while (tokens[i] && is_operator(tokens[i]) == NONE)
		i++;
	node->args = malloc(sizeof(char *) * i);
	node->args[i - 1] = NULL;
	*step += i;
	while (--i > 0)
	{
		if (ft_strnstr(tokens[i], "*.", ft_strlen(tokens[i]))
			&& get_matching_files(tokens[i]))
			node->args[i - 1] = get_matching_files(tokens[i]);
		else
			node->args[i - 1] = ft_strdup(tokens[i]);
	}
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_shunting_yard	*shunting_yard_create(char	**tokens)
{
	t_shunting_yard	*yard;
	t_shunting_node	*temp;
	int				step;

	step = 0;
	yard = (t_shunting_yard *)malloc(sizeof(t_shunting_yard));
	if (!yard || !tokens || !*tokens)
		return (NULL);
	yard->output = NULL;
	yard->stack = NULL;
	yard->input = NULL;
	if (!yard || !tokens || !*tokens)
		return (NULL);
	while (tokens + step)
	{
		temp = shunting_node_new(tokens + step, &step);
		if (!temp)
			break ;
		if (yard->output == NULL)
			yard->output = temp;
		else
		{
			temp->prev = yard->output;
			yard->output->next = temp;
			yard->output = yard->output->next;
		}
	}
	while (yard->output->prev)
		yard->output = yard->output->prev;
	yard->stack = NULL;
	yard->input = yard->output;
	yard->output = NULL;
	return (yard);
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
