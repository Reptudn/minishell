/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:00:18 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/27 15:44:57 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// TODO: this has to take an argument which is the exit code the user wants to
// exit the shell

bool	arg_is_numerical(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_exit(t_shell *shell, t_shunting_node *cmd)
{
	int	exit_code;

	exit_code = CMD_SUCCESS;
	shell->run = false;
	if (!cmd->args)
		return (exit_code);
	if (ft_strlen(cmd->args) > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
		return (CMD_FAILURE);
	}
	if (!arg_is_numerical(cmd->args))
	{
		ft_putstr_fd("minishell: exit: ", 1);
		ft_putstr_fd(cmd->args, 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		return (CMD_FAILURE);
	}
	exit_code = ft_atoi(cmd->args);
	return (exit_code % 255);
}
