/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:58:11 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 13:36:58 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_invalid_cmd(char *command, char *error, int exit)
{
	ft_putstr_fd((char *)color_red(), 2);
	ft_putstr_fd((char *)color_red(), 2);
	ft_putstr_fd("minishell: command not found: `", 2);
	ft_putstr_fd((char *)color_magenta(), 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd((char *)color_red(), 2);
	ft_putstr_fd("` | error: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(" | exit: ", 2);
	ft_putnbr_fd(exit, 2);
	ft_putstr_fd((char *)color_reset(), 2);
	ft_putstr_fd("\n", 2);
}
