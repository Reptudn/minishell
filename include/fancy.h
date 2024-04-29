/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fancy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:49:40 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/25 12:17:26 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FANCY_H
# define FANCY_H

# include <term.h>
# include <unistd.h>

void	move_cursor_left_offset(int offset);
void	move_cursor_right_offset(int offset);
void	move_cursor_relative(int x, int y);
void	move_cursor(int x, int y);

void	print_name(void);
void	print_path(void);

#endif