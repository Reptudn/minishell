/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:35:08 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/15 13:36:18 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(t_shunting_node *cmd, t_shell *shell)
{
	int	i;
	int	found;

	i = -1;
	found = CMD_FAILURE;
	while (shell->envp[++i])
	{
		if (ft_strncmp(shell->envp[i], cmd->args[0],
				ft_strlen(cmd->args[0])) == 0)
		{
			shell->envp[i] = "\033[0;31mhas been unset\033[0m";
			found = CMD_SUCCESS;
			break ;
		}
	}
	return (found);
}
