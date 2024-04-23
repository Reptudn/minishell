/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:37:51 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/22 16:44:31 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <term.h>

void	draw_border()
{
	char *termtype = getenv("TERM");
    char term_buffer[2048];
    char *cm, *so, *se;
    char *output;
    int rows, cols, i;

    // Get the "cm" (cursor motion), "so" (start standout), and "se" (end standout) capabilities
    tgetent(term_buffer, termtype);
    cm = tgetstr("cm", &output);
    so = tgetstr("so", &output);
    se = tgetstr("se", &output);

    // Get the size of the terminal
    rows = tgetnum("li");
    cols = tgetnum("co");

    // Draw the top and bottom borders
    for (i = 0; i < cols; i++) {
        output = tgoto(cm, i, 0);
        tputs(output, 1, putchar);
        tputs(so, 1, putchar);
        write(1, "*", 1);
        tputs(se, 1, putchar);

        output = tgoto(cm, i, rows - 1);
        tputs(output, 1, putchar);
        tputs(so, 1, putchar);
		write(1, "*", 1);
        tputs(se, 1, putchar);
    }

    // Draw the left and right borders
    for (i = 0; i < rows; i++) {
        output = tgoto(cm, 0, i);
        tputs(output, 1, putchar);
        tputs(so, 1, putchar);
        write(1, "*", 1);
        tputs(se, 1, putchar);

        output = tgoto(cm, cols - 1, i);
        tputs(output, 1, putchar);
        tputs(so, 1, putchar);
        write(1, "*", 1);
        tputs(se, 1, putchar);
    }
}