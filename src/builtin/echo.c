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

void	remove_surrounding_singleq(char *str)
{
	if (str[0] != '\'' || str[ft_strlen(str) - 1] != '\'')
		return ;
	ft_memmove(str, str + 1, ft_strlen(str) - 2);
	str[ft_strlen(str) - 2] = '\0';
}

//TODO: echo '$ANTHING' should display $ANTHING and not the value of the variable
int	ft_echo(t_shunting_node *cmd)
{
	int		i;
	int		nl;

	i = -1;
	nl = 1;
	if (!cmd)
		return (CMD_FAILURE);
	remove_surrounding_singleq(cmd->args[0]);
	if (cmd->args && str_is_equal(cmd->args[0], "-n"))
	{
		nl = 0;
		i++;
	}
	while (cmd->args && cmd->args[++i])
	{
		remove_surrounding_singleq(cmd->args[i]);
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
	}
	if (nl)
		printf("\n");
	return (CMD_SUCCESS);
}
