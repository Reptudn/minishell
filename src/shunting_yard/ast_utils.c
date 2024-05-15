/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:06:59 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/06 15:22:27 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
**	TODO: check if those prio values are all correct
**	 and fit with shunting_yard_node.c:28 that checks forthe pro to
**	 be less than or equal to the prio of the last node in the stack
*/
int	get_operator_priority(char *operator)
{
	if (operator && ft_strlen(operator) == 1)
	{
		if (str_is_equal(operator, "|") == 1)
			return (1);
		if (str_is_equal(operator, ">") == 1)
			return (2);
		if (str_is_equal(operator, "<") == 1)
			return (2);
		if (str_is_equal(operator, "(") == 1)
			return (3);
		if (str_is_equal(operator, ")") == 1)
			return (3);
	}
	else if (operator && ft_strlen(operator) == 2)
	{
		if (str_is_equal(operator, "||") == 1)
			return (1);
		if (str_is_equal(operator, "&&") == 1)
			return (1);
		if (str_is_equal(operator, ">>") == 1)
			return (2);
		if (str_is_equal(operator, "<<") == 1)
			return (2);
	}
	return (0);
}
