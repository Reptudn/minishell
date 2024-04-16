/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:28:17 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/16 20:34:29 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*color_black(void)
{
	if (isatty(STDOUT_FILENO))
		return (COLOR_BLACK);
	return ("");
}

char	*color_red(void)
{
	if (isatty(STDOUT_FILENO))
		return (COLOR_RED);
	return ("");
}

char	*color_green(void)
{
	if (isatty(STDOUT_FILENO))
		return (COLOR_GREEN);
	return ("");
}

char	*color_yellow(void)
{
	if (isatty(STDOUT_FILENO))
		return (COLOR_YELLOW);
	return ("");
}

char	*color_blue(void)
{
	if (isatty(STDOUT_FILENO))
		return (COLOR_BLUE);
	return ("");
}
