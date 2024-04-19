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

char	*remove_surrounding_singleq(char *str)
{
	if (!str || str[0] != '\'' || str[ft_strlen(str) - 1] != '\'')
		return (str);
	ft_memmove(str, str + 1, ft_strlen(str) - 2);
	str[ft_strlen(str) - 2] = '\0';
	return (str);
}

bool	is_new_line(char *str)
{
	int	i;

	if (!str)
		return (false);
	if (str[0] != '-')
		return (false);
	i = 0;
	while (str[++i])
		if (str[i] != 'n')
			return (false);
	return (true);
}

int	ft_echo(t_shunting_node *cmd)
{
	int		i;
	int		nl;

	i = -1;
	nl = 1;
	if (!cmd)
		return (CMD_FAILURE);
	while (cmd->args
		&& is_new_line(remove_surrounding_singleq(cmd->args[++i])))
		nl = 0;
	i--;
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
