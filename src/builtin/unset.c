/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:35:08 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/15 12:26:14 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(t_shunting_node *cmd, t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->envp[++i])
	{
		if (str_is_equal(shell->envp[i], cmd->args[1]))
		{
			free(shell->envp[i]);
			while (shell->envp[i])
			{
				shell->envp[i] = shell->envp[i + 1];
				i++;
			}
			break ;
		}
	}
	return (0);
}
