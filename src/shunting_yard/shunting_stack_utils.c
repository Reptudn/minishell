/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_stack_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:36:34 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/02 13:53:01 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// removed one node from the stack and changes the pointers so everything is
// connected again even if the node was in the middle of the stack
// only for output
void	yard_pop(t_shunting_node *pop, t_shunting_yard *yard)
{
	int	i;

	i = -1;
	if (!pop)
		return ;
	if (pop->prev)
		pop->prev->next = pop->next;
	if (pop->next)
		pop->next->prev = pop->prev;
	if (yard->output == pop)
	{
		yard->output = pop->next;
		if (yard->output)
			yard->output->prev = NULL;
	}
	if (pop->value)
		free(pop->value);
	if (pop->args)
		while (pop->args[++i])
			free(pop->args[i]);
	free(pop->args);
	free(pop->type);
	free(pop->priority);
	free(pop->exit_status);
	free(pop);
}
