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

int		get_str_arr_len(char **arr);
bool	arg_is_numerical(char *arg);
void	error_exit(t_shell *shell, t_shunting_node *cmd);

long	ft_atol(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return ((long)(result * sign));
}

int	ft_exit_helper(t_shunting_node *cmd, t_shell *shell)
{
	if (!arg_is_numerical(cmd->args[0]) || ft_strlen(cmd->args[0]) > 20)
	{
		if (cmd->args[0])
			error_exit(shell, cmd);
		*shell->exit_status = 2;
		return (2);
	}
	ft_putstr_fd("minishell: exit: too many arguments\n", 1);
	*shell->exit_status = 1;
	return (0);
}

int	exit_code_helper(long *exit_code, t_shunting_node *cmd)
{
	*exit_code = ft_atol(cmd->args[0]);
	if (*exit_code < 0)
		*exit_code = 256 + *exit_code;
	return (*exit_code);
}

int	ft_exit(t_shell *shell, t_shunting_node *cmd)
{
	long	exit_code;

	exit_code = CMD_SUCCESS;
	*get_run() = 0;
	if (!cmd->args || !cmd->args[0])
		return (exit_code);
	if (get_str_arr_len(cmd->args) > 1)
	{
		if (ft_exit_helper(cmd, shell))
			return (2);
		return (1);
	}
	else if (!arg_is_numerical(cmd->args[0]) || ft_strlen(cmd->args[0]) > 20)
	{
		if (cmd->args[0])
			error_exit(shell, cmd);
		*shell->exit_status = 2;
		return (2);
	}
	while (*cmd->args[0] == '0')
		cmd->args[0]++;
	exit_code = exit_code_helper(&exit_code, cmd);
	*shell->exit_status = exit_code % 256;
	return (exit_code % 256);
}
