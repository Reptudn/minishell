/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 13:05:40 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/16 12:27:29 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_pwd_helper_helper_fuck_norminette(char *new_path, char *old_path)
{
	// ft_free((new_path));
	// ft_free((old_path));
}

int	set_pwd_helper(t_env_var *tmp, t_env_var *oldpwd,
		char *new_path, char *old_path)
{
	t_shell	*shell;

	if (tmp)
	{
		if (tmp->value)
			// ft_free((tmp->value));
		tmp->value = ft_strdup(new_path);
		if (!tmp->value)
		{
			// ft_free((new_path));
			// ft_free((old_path));
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
		// ft_free((oldpwd->value));
		oldpwd->value = ft_strdup(old_path);
		if (!oldpwd->value)
		{
			// ft_free((new_path));
			// ft_free((old_path));
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

int	handle_same_path(t_shunting_node *cmd, char *old_path)
{
	if (cmd->args && str_is_equal(cmd->args[0], old_path))
	{
		// ft_free((old_path));
		return (CMD_SUCCESS);
	}
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
