/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:36:09 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/25 15:51:15 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_echo(t_shunting_node *cmd)
{
	int	i;
	int	nl;

	i = -1;
	nl = 1;
	if (!cmd)
		return (CMD_FAILURE);
	if (cmd->args && str_is_equal(cmd->args[0], "-n"))
	{
		nl = 0;
		i++;
	}
	while (cmd->args && cmd->args[++i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
	}
	if (nl)
		printf("\n");
	return (CMD_SUCCESS);
}
