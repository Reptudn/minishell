/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:41:33 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/18 09:38:35 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../include/minishell.h"

int	is_operator(char *str)
{
	if (str && ft_strlen(str) == 1)
	{
		if (str_is_equal(str, "|") == 1)
			return (PIPE);
		if (str_is_equal(str, ">") == 1)
			return (REDIRECT_OUT);
		if (str_is_equal(str, "<") == 1)
			return (REDIRECT_IN);
		if (str_is_equal(str, "(") == 1)
			return (OPEN_PAREN);
		if (str_is_equal(str, ")") == 1)
			return (CLOSE_PAREN);
	}
	else if (str && ft_strlen(str) == 2)
	{
		if (str_is_equal(str, "||") == 1)
			return (OR);
		if (str_is_equal(str, "&&") == 1)
			return (AND);
		if (str_is_equal(str, ">>") == 1)
			return (REDIRECT_OUT_APPEND);
		if (str_is_equal(str, "<<") == 1)
			return (REDIRECT_IN_DELIMITER);
	}
	return (NONE);
}

int	str_is_equal(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

int	is_env_command(t_shell *shell, char *str)
{
	char		*cmd_path;
	char		*tmp;
	t_env_var	*path;
	char		**split;
	int			i;

	i = -1;
	path = env_get_by_name(shell->env_vars, "PATH");
	if (!path)
		return (0);
	split = ft_split(path->value, ':');
	if (!split)
		return (0);
	while (split[++i])
	{
		cmd_path = ft_strjoin(split[i], "/");
		if (!cmd_path)
			return (0);
		tmp = ft_strjoin(cmd_path, str);
		free(cmd_path);
		cmd_path = tmp;
		if (!cmd_path)
		{
			free(cmd_path);
			return (0);
		}
		if (access(cmd_path, F_OK) == 0)
		{
			free(cmd_path);
			return (1);
		}
		free(cmd_path);
	}
	return (0);
}

int	is_command(char *str, t_shell *shell)
{
	if (str_is_equal("echo", str) == 1)
		return (1);
	if (str_is_equal("pwd", str) == 1)
		return (1);
	if (str_is_equal("clear", str) == 1)
		return (1);
	if (str_is_equal("export", str) == 1)
		return (1);
	if (str_is_equal("env", str) == 1)
		return (1);
	if (str_is_equal("unset", str) == 1)
		return (1);
	if (str_is_equal("cd", str) == 1)
		return (1);
	if (str_is_equal("history", str) == 1)
		return (1);
	if (str_is_equal("exit", str) == 1)
		return (1);
	if (is_env_command(shell, str) == 1)
		return (1);
	return (0);
}
