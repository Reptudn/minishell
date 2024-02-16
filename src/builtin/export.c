/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:35:05 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/16 15:04:33 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_export(t_shell *shell)
{
	int	i;

	i = -1;
	if (!shell->envp)
	{
		printf("no envp\n");
		return (1);
	}
	while (shell->envp[++i])
	{
		if (!shell->envp[i])
		{
			printf("no envp arg\n");
			continue ;
		}
		ft_putstr_fd(shell->envp[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (0);
}
