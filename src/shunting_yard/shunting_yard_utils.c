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

int			get_operator_priority(char *operator);

t_shunting_node	*shunting_node_init(char	**tokens)
{
	t_shunting_node	*node;

	if (!tokens || !*tokens)
		return (NULL);
	node = (t_shunting_node *)malloc(sizeof(t_shunting_node));
	if (!node)
		return (NULL);
	node->type = malloc(sizeof(int));
	node->priority = malloc(sizeof(int));
	node->exit_status = malloc(sizeof(int));
	node->update = 1;
	*node->exit_status = -1;
	*node->type = is_operator(tokens[0]);
	*node->priority = get_operator_priority(tokens[0]);
	node->value = ft_strdup(tokens[0]); //TODO: here is a leak
	node->args = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_shunting_node	*shunting_node_new(char	**tokens, int *step)
{
	t_shunting_node	*node;
	int				i;

	node = shunting_node_init(tokens);
	if (!node)
		return (NULL);
	if (is_operator(tokens[0]) != NONE)
	{
		*step += 1;
		return (node);
	}
	i = 0;
	while (tokens[i] && is_operator(tokens[i]) == NONE)
		i++;
	node->args = malloc(sizeof(char *) * i); // TODO: here is a leak
	node->args[i - 1] = NULL;
	*step += i;
	while (--i > 0)
		node->args[i - 1] = ft_strdup(tokens[i]);
	return (node);
}

t_shunting_yard	*shunting_yard_init(char	**tokens)
{
	t_shunting_yard	*yard;

	yard = (t_shunting_yard *)malloc(sizeof(t_shunting_yard));
	if (!yard || !tokens || !*tokens)
		return (NULL);
	yard->output = NULL;
	yard->stack = NULL;
	yard->input = NULL;
	return (yard);
}

t_shunting_yard	*finish_yard(t_shunting_yard *yard)
{
	while (yard->output && yard->output->prev)
		yard->output = yard->output->prev;
	yard->stack = NULL;
	yard->input = yard->output;
	yard->output = NULL;
	return (yard);
}

t_shunting_yard	*shunting_yard_create(char	**tokens)
{
	t_shunting_yard	*yard;
	t_shunting_node	*temp;
	int				step;

	step = 0;
	yard = shunting_yard_init(tokens);
	if (!yard)
		return (NULL);
	while (tokens[step]) //TODO: somewhere in here the leaks are generated
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
	return (finish_yard(yard));
}
