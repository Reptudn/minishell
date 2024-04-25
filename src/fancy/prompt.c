/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 06:28:44 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/25 10:01:00 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <term.h>

void	print_path(void)
{
	t_prompt	prompt;
	t_shell		*shell;
	t_env_var	*path;
	t_env_var	*term;

	if (!isatty(fileno(stdin)))
		return ;
	term = env_get_by_name(get_shell()->env_vars, "TERM");
	if (!term || !term->value || tgetent(prompt.term_buffer, term->value) != 1)
		return ;
	path = env_get_by_name(get_shell()->env_vars, "PWD");
	shell = get_shell();
	printf("path value: %s\n", path->value);
	prompt.col = tgetnum("co");
	prompt.original_pos = tgetnum("cc");
	prompt.position = prompt.col - ft_strlen(path->value);
	prompt.move_cursor = tgoto(tgetstr("ch", NULL), 0, prompt.position);
	tputs(prompt.move_cursor, 1, putchar);
	tputs((char *)color_green(), 1, putchar);
	if (path && path->value)
		tputs(path->value, 1, putchar);
	tputs((char *)color_reset(), 1, putchar);
	prompt.move_cursor = tgoto(tgetstr("ch", NULL), 0, prompt.original_pos);
	tputs(prompt.move_cursor, 1, putchar);
}
