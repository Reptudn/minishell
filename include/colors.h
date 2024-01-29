/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:49:40 by jkauker           #+#    #+#             */
/*   Updated: 2024/01/29 11:58:07 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

// https://www.codeproject.com/Articles/5329247/How-to-Change-Text-Color-in-a-Linux-Terminal

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

#endif