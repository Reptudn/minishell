/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:58:19 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/13 13:43:56 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_operator_count(t_shunting_node *nodes)
{
	int	count;

	count = 0;
	while (nodes)
	{
		count++;
		if (*nodes->type == NONE || *nodes->type == OPEN_PAREN
			|| *nodes->type == CLOSE_PAREN)
			count--;
		nodes = nodes->next;
	}
	return (count);
}

t_shunting_node	*get_operator_with_index(t_shunting_node *nodes, int index)
{
	if (index < 1 || index > get_operator_count(nodes))
		return (NULL);
	while (nodes)
	{
		if (*nodes->type != NONE)
		{
			if (index == 1)
				return (nodes);
			index--;
		}
		nodes = nodes->next;
	}
	return (NULL);
}
