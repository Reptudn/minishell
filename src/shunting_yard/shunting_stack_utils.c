/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_stack_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:36:34 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/21 12:08:33 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// removed one node from the stack and changes the pointers so everything is connected again even if the node was in the middle of the stack
// only for output
void yard_pop(t_shunting_node *pop, t_shunting_yard *yard)
{
	if (!pop)
		return ;
	if (pop->prev)
		pop->prev->next = pop->next;
	if (pop->next)
		pop->next->prev = pop->prev;
	if (yard->output == pop)
		yard->output = pop->next;
	// free_node(pop);
}
