/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:35:08 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/18 10:06:13 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(t_shunting_node *cmd, t_shell *shell)
{
	t_env_var	*found;

	if (!cmd->args[0])
	{
		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
		*shell->exit_status = 0;
		return (CMD_SUCCESS);
	}
	found = env_get_by_name(shell->env_vars, cmd->args[0]);
	if (!found)
		return (CMD_SUCCESS);
	if (str_is_equal(cmd->args[0], "SHLVL"))
	{
		free(found->value);
		found->value = ft_strdup("0");
	}
	else
		env_pop(shell->env_vars, found);
	return (CMD_SUCCESS);
}

