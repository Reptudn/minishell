/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 10:06:48 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/12 10:17:13 by jkauker          ###   ########.fr       */
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

void	error_exit(t_shell *shell, t_shunting_node *cmd)
{
	ft_putstr_fd("minishell: exit: ", 1);
	ft_putstr_fd(cmd->args[0], 1);
	ft_putstr_fd(": numeric argument required\n", 1);
	*shell->exit_status = CMD_FAILURE;
}
