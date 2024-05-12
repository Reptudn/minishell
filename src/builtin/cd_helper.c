/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 13:05:40 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/12 13:06:04 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_pwd_helper_helper_fuck_norminette(char *new_path, char *old_path)
{
	free(new_path);
	free(old_path);
}

int	set_pwd_helper(t_env_var *tmp, t_env_var *oldpwd,
		char *new_path, char *old_path)
{
	t_shell	*shell;

	if (tmp)
	{
		if (tmp->value)
			free(tmp->value);
		tmp->value = ft_strdup(new_path);
		if (!tmp->value)
		{
			free(new_path);
			free(old_path);
			return (CMD_FAILURE);
		}
	}
	else
	{
		tmp = env_create_var("PWD", new_path, true);
		if (!tmp)
		{
			set_pwd_helper_helper_fuck_norminette(new_path, old_path);
			return (CMD_FAILURE);
		}
		env_push(shell->env_vars, tmp);
	}
	return (0);
}

int	set_pwd_helper2(t_env_var *oldpwd, char *old_path,
		char *new_path, t_shell *shell)
{
	if (oldpwd)
	{
		free(oldpwd->value);
		oldpwd->value = ft_strdup(old_path);
		if (!oldpwd->value)
		{
			free(new_path);
			free(old_path);
			return (CMD_FAILURE);
		}
	}
	else
	{
		oldpwd = env_create_var("OLDPWD", old_path, true);
		env_push(shell->env_vars, oldpwd);
	}
	return (0);
}
