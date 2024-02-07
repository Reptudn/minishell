/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:36:09 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/07 12:39:24 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_echo(t_command *cmd)
{
	int	i;

	i = 0;
	if (ft_strncmp(cmd->command, "echo", ft_strlen(cmd->command)) != 0)
		return (0);
	while (cmd->args[i])
	{
		// printf("%s", cmd->args[i]);
		i++;
	}
	printf("\n");
	return (1);
}
