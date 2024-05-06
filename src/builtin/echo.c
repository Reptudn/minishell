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

char	*remove_surrounding_singleq(char *str, int *changed)
{
	if (!str || !*str
		|| (ft_strlen(str) == 2 && str[0] == '\'' && str[1] == '\''))
	{
		if (changed)
			*changed = 1;
		return (ft_strdup(""));
	}
	else if (ft_strlen(str) < 2)
	{
		if (changed)
			*changed = 1;
		return (str);
	}
	if (!str || !*str || (str[0] != '\'' && str[ft_strlen(str) - 1] != '\''))
		return (str);
	ft_memmove(str, str + 1, ft_strlen(str) - 2);
	str[ft_strlen(str) - 2] = '\0';
	if (changed)
		*changed = 1;
	return (str);
}

char	*remove_surrounding_doubleq(char *str, int *changed)
{
	if (!str || !*str
		|| (ft_strlen(str) == 2 && str[0] == '"' && str[1] == '"'))
	{
		if (changed)
			*changed = 1;
		return (ft_strdup(""));
	}
	else if (ft_strlen(str) < 2)
	{
		if (changed)
			*changed = 1;
		return (str);
	}
	if (!str || !*str || (str[0] != '"' && str[ft_strlen(str) - 1] != '"'))
		return (str);
	ft_memmove(str, str + 1, ft_strlen(str) - 2);
	str[ft_strlen(str) - 2] = '\0';
	if (changed)
		*changed = 1;
	return (str);
}

bool	is_valid_flag(char *str)
{
	if (str[0] != '-')
		return (false);
	str++;
	while (*str == 'n')
		str++;
	return (ft_isspace(*str) || *str == '\0');
}

char	*get_first(char *str)
{
	while (*str)
	{
		if (is_valid_flag(str))
		{
			while (*str != ' ' && *str != '\0')
				str++;
			while (ft_isspace(*str))
				str++;
		}
		else
			return (str);
	}
	return (str);
}

int	args_len(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}

int	ft_echo(t_shunting_node *cmd)
{
	int		i;
	int		nl;
	int		c;
	int		len;

	i = -1;
	nl = 1;
	if (!cmd)
		return (CMD_FAILURE);
	while (cmd->args && cmd->args[++i]
		&& is_valid_flag(cmd->args[i]))
		nl = 0;
	i -= 2;
	if (i < -1)
		i = -1;
	c = i;
	len = args_len(cmd->args);
	while (cmd->args && cmd->args[++i] && i < len - 1)
	{
		if (c == i - 1)
		{
			if (*(cmd->args[i]) == 0)
				printf(" ");
			else if (*get_first(cmd->args[i]) == 0)
				continue ;
			else
				printf("%s", get_first(cmd->args[i]));
		}
		else if (*(cmd->args[i]) == '\0')
			printf(" ");
		else
			printf("%s", cmd->args[i]);
		if (*(cmd->args[i]) != 0 && i < len - 2)
			printf(" ");
	}
	if (nl)
		printf("\n");
	return (CMD_SUCCESS);
}
