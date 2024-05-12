/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 06:28:44 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/12 13:26:36 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <term.h>

void	move_cursor_left_offset(int offset)
{
	char	*cap;

	cap = tgetstr("le", NULL);
	while (offset--)
		tputs(cap, 1, putchar);
}

void	move_cursor_right_offset(int offset)
{
	char	*cap;

	cap = tgetstr("nd", NULL);
	while (offset--)
		tputs(cap, 1, putchar);
}

void	move_cursor_relative_helper(int *x, int *y, char *cap)
{
	if (*y > 0)
	{
		cap = tgetstr("do", NULL);
		while (*y--)
			tputs(cap, 1, putchar);
	}
	else if (*y < 0)
	{
		cap = tgetstr("up", NULL);
		*y = -(*y);
		while (*y--)
			tputs(cap, 1, putchar);
	}
}

void	move_cursor_relative(int x, int y)
{
	char	*cap;

	if (x > 0)
	{
		cap = tgetstr("nd", NULL);
		while (x--)
			tputs(cap, 1, putchar);
	}
	else if (x < 0)
	{
		cap = tgetstr("le", NULL);
		x = -x;
		while (x--)
			tputs(cap, 1, putchar);
	}
	move_cursor_relative_helper(&x, &y, cap);
}

void	move_cursor(int x, int y)
{
	char	*cap;
	char	*command;

	cap = tgetstr("cm", NULL);
	if (cap != NULL)
	{
		command = tgoto(cap, x, y);
		tputs(command, 1, putchar);
	}
}
