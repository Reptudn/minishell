/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:55:33 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/16 14:49:15 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	command_loop_helper2(t_shunting_yard *yard, char *line, int status)
{
	if (!yard)
	{
		line = get_input(prompt_failure());
		status = CMD_FAILURE;
		return (1);
	}
	return (0);
}

int	command_loop_helper(char *line)
{
	if (ft_strlen(line) == 0)
	{
		line = get_input(prompt_success());
		if (!line)
		{
			*get_run() = 0;
			return (1);
		}
		return (1);
	}
	return (0);
}

int	command_loop_helper3(char *line, t_shunting_yard **yard, int status)
{
	if (command_loop_helper(line))
		return (1);
	*yard = shunting_yard(ft_split_shell(is_valid_input(line)));
	if (command_loop_helper2(*yard, line, status))
		return (1);
	return (0);
}
