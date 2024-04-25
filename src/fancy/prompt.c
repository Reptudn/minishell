/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 06:28:44 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/25 12:28:32 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/fancy.h"
#include <term.h>

void	print_name(void)
{
	t_env_var	*user;
	t_env_var	*host;

	user = env_get_by_name(get_shell()->env_vars, "USER");
	host = env_get_by_name(get_shell()->env_vars, "HOSTNAME");
	move_cursor_relative(0, 1);
	if (!(user && user->value && host && host->value))
	{
		if (user && user->value)
		{
			move_cursor_right_offset(ft_strlen(user->value));
			tputs(user->value, 1, putchar);
		}
		return ;
	}
	move_cursor_right_offset(ft_strlen(user->value)
		+ ft_strlen(host->value) + 1);
	tputs(user->value, 1, putchar);
	tputs("@", 1, putchar);
	tputs(host->value, 1, putchar);
}

void	print_path(void)
{
	t_prompt	prompt;
	t_env_var	*path;
	t_env_var	*term;

	if (!isatty(fileno(stdin)))
		return ;
	term = env_get_by_name(get_shell()->env_vars, "TERM");
	if (!term || !term->value || tgetent(prompt.term_buffer, term->value) != 1)
		return ;
	path = env_get_by_name(get_shell()->env_vars, "PWD");
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
