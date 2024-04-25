/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 06:28:44 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/25 06:52:11 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <term.h>

void	print_path(void)
{
	int		original_pos;
	int		col;
	char	*move_cursor;
	int		position;
	char	term_buffer[2048];
	char	*term_type = getenv("TERM");
	t_shell	*shell;

	if (!isatty(fileno(stdin)))
		return ;

	if (tgetent(term_buffer, term_type) != 1)
	{
		printf("not in db\n");
		return ;
	}

	shell = get_shell();
	col = tgetnum("co");
	original_pos = tgetnum("cc");
	position = col - strlen(shell->path) - 1;
	move_cursor = tgoto(tgetstr("ch", NULL), 0, position);
	tputs(move_cursor, 1, putchar);
	tputs((char *)color_green(), 1, putchar);
	tputs(shell->path, 1, putchar);
	tputs((char *)color_reset(), 1, putchar);
	tputs(" ", 1, putchar);
	move_cursor = tgoto(tgetstr("ch", NULL), 0, original_pos);
	tputs(move_cursor, 1, putchar);
	original_pos--;
}
