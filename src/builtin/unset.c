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
	int			i;

	i = -1;
	if (!cmd->args[0] || !cmd->args)
	{
		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
		*shell->exit_status = 0;
		return (CMD_SUCCESS);
	}
	while (cmd->args[++i])
	{
		found = env_get_by_name(shell->env_vars, cmd->args[i]);
		if (!found)
			continue ;
		if (str_is_equal(cmd->args[i], "SHLVL"))
		{
			ft_free((found->value));
			found->value = ft_strdup("0");
		}
		else
			env_pop(shell->env_vars, found);
	}
	return (CMD_SUCCESS);
}
