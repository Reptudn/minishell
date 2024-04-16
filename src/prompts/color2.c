/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:28:20 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/16 20:34:45 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*color_magenta(void)
{
	if (isatty(STDOUT_FILENO))
		return (COLOR_MAGENTA);
	return ("");
}

char	*color_cyan(void)
{
	if (isatty(STDOUT_FILENO))
		return (COLOR_CYAN);
	return ("");
}

char	*color_white(void)
{
	if (isatty(STDOUT_FILENO))
		return (COLOR_WHITE);
	return ("");
}

char	*color_reset(void)
{
	if (isatty(STDOUT_FILENO))
		return (COLOR_RESET);
	return ("");
}
