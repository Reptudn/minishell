/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 06:28:44 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/25 09:40:10 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <term.h>

void	print_path(void)
{
	t_prompt	prompt;
	t_shell		*shell;
	t_env_var	*path;

	if (!isatty(fileno(stdin)))
		return ;
	prompt.term_type = env_get_by_name(get_shell()->env_vars, "TERM");
	if (tgetent(prompt.term_buffer, prompt.term_type) != 1)
		return ;
	path = env_get_by_name(get_shell()->env_vars, "PWD");
	shell = get_shell();
	prompt.col = tgetnum("co");
	prompt.original_pos = tgetnum("cc");
	prompt.position = prompt.col - ft_strlen(path);
	prompt.move_cursor = tgoto(tgetstr("ch", NULL), 0, prompt.position);
	tputs(prompt.move_cursor, 1, putchar);
	tputs((char *)color_green(), 1, putchar);
	if (path)
		tputs(path->value, 1, putchar);
	tputs((char *)color_reset(), 1, putchar);
	prompt.move_cursor = tgoto(tgetstr("ch", NULL), 0, prompt.original_pos);
	tputs(prompt.move_cursor, 1, putchar);
}
