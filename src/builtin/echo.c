/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:36:09 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/14 09:47:05 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_echo(t_shunting_node *cmd)
{
	int	i;

	i = -1;
	if (!cmd)
		return (CMD_FAILURE);
	if (ft_strncmp(cmd->value, "echo", ft_strlen(cmd->value)) != 0)
		return (1);
	while (cmd->args[++i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
	}
	printf("\n");
	return (CMD_SUCCESS);
}
