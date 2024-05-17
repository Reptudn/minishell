/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsabia <nsabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 13:05:40 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/17 12:27:15 by nsabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	set_pwd_helper(t_env_var *tmp, t_env_var *oldpwd,
		char *new_path, char *old_path)
{
	t_shell	*shell;

	(void)old_path;
	(void)oldpwd;
	shell = NULL;
	if (tmp)
	{
		tmp->value = ft_strdup(new_path);
		if (!tmp->value)
			return (CMD_FAILURE);
	}
	else
	{
		tmp = env_create_var("PWD", new_path, true);
		if (!tmp)
			return (CMD_FAILURE);
		env_push(shell->env_vars, tmp);
	}
	return (0);
}

int	set_pwd_helper2(t_env_var *oldpwd, char *old_path,
		char *new_path, t_shell *shell)
{
	(void)new_path;
	if (oldpwd)
	{
		oldpwd->value = ft_strdup(old_path);
		if (!oldpwd->value)
			return (CMD_FAILURE);
	}
	else
	{
		oldpwd = env_create_var("OLDPWD", old_path, true);
		env_push(shell->env_vars, oldpwd);
	}
	return (0);
}

int	handle_same_path(t_shunting_node *cmd, char *old_path)
{
	if (cmd->args && str_is_equal(cmd->args[0], old_path))
		return (CMD_SUCCESS);
	return (CMD_FAILURE);
}

char	*handle_home_path(t_shunting_node *cmd, t_shell *shell, char *new_path)
{
	t_env_var	*tmp;

	if (!cmd->args || !cmd->args[0] || ((cmd->args)[0] != 0
		&& str_is_equal(cmd->args[0], "~")))
	{
		tmp = env_get_by_name(shell->env_vars, "HOME");
		if (!tmp)
			new_path = NULL;
		else
			new_path = tmp->value;
	}
	else
		new_path = (cmd->args)[0];
	return (new_path);
}

char	*ft_getcwd(char *str, int num)
{
	char	*str_return;
	char	*str2;

	str_return = getcwd(str, num);
	str2 = ft_strdup(str_return);
	free(str_return);
	return (str2);
}
