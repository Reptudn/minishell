/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:00:18 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/02 12:14:24 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_str_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

bool	arg_is_numerical(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (false);
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
	if (get_str_arr_len(cmd->args) > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
		*shell->exit_status = CMD_FAILURE;
		return (CMD_FAILURE);
	}
	if (!arg_is_numerical(cmd->args[0]))
	{
		*shell->exit_status = CMD_FAILURE;
		return (CMD_FAILURE);
	}
	exit_code = ft_atoi(cmd->args[0]);
	*shell->exit_status = exit_code % 256;
	return (exit_code % 256);
}
