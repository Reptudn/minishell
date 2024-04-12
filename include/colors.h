/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:49:40 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/11 08:57:20 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include <unistd.h>

// Foreground colors
# define COLOR_BLACK "\033[0;30m"
# define COLOR_RED "\033[0;31m"
# define COLOR_GREEN "\033[0;32m"
# define COLOR_YELLOW "\033[0;33m"
# define COLOR_BLUE "\033[0;34m"
# define COLOR_MAGENTA "\033[0;35m"
# define COLOR_CYAN "\033[0;36m"
# define COLOR_WHITE "\033[0;37m"

// Background colors
# define COLOR_BG_RED "\033[41m"
# define COLOR_BG_GREEN "\033[42m"
# define COLOR_BG_YELLOW "\033[43m"
# define COLOR_BG_BLUE "\033[44m"
# define COLOR_BG_MAGENTA "\033[45m"
# define COLOR_BG_CYAN "\033[46m"
# define COLOR_BG_WHITE "\033[47m"

# define COLOR_RESET "\033[0m"

static inline const char	*color_black(void)
{
	if (isatty(STDOUT_FILENO))
		return (COLOR_BLACK);
	return ("");
}

static inline const char	*color_red(void)
{
	if (isatty(STDOUT_FILENO))
		return (COLOR_RED);
	return ("");
}

static inline const char	*color_green(void)
{
	if (isatty(STDOUT_FILENO))
		return (COLOR_GREEN);
	return ("");
}

static inline const char	*color_yellow(void)
{
	if (isatty(STDOUT_FILENO))
		return (COLOR_YELLOW);
	return ("");
}

static inline const char	*color_blue(void)
{
	if (isatty(STDOUT_FILENO))
		return (COLOR_BLUE);
	return ("");
}

static inline const char	*color_magenta(void)
{
	if (isatty(STDOUT_FILENO))
		return (COLOR_MAGENTA);
	return ("");
}

static inline const char	*color_cyan(void)
{
	if (isatty(STDOUT_FILENO))
		return (COLOR_CYAN);
	return ("");
}

static inline const char	*color_white(void)
{
	if (isatty(STDOUT_FILENO))
		return (COLOR_WHITE);
	return ("");
}

static inline const char	*color_reset(void)
{
	if (isatty(STDOUT_FILENO))
		return (COLOR_RESET);
	return ("");
}

#endif