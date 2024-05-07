/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:21:48 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/11 09:52:08 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	echo_err(char *new_path)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	if (!new_path)
		ft_putstr_fd("HOME not set", STDERR_FILENO);
	else
		ft_putstr_fd(new_path, STDERR_FILENO);
	if (new_path)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}

//TODO: check if you need to free old_path
int	set_pwd(t_shell *shell, char *old_path)
{
	t_env_var	*tmp;
	t_env_var	*oldpwd;
	char		*new_path;

	new_path = getcwd(NULL, 0);
	if (!new_path)
	{
		echo_err(NULL);
		return (CMD_FAILURE);
	}
	tmp = env_get_by_name(shell->env_vars, "PWD");
	if (tmp)
	{
		if (tmp->value)
			free(tmp->value);
		tmp->value = new_path;
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
			free(new_path);
			free(old_path);
			return (CMD_FAILURE);
		}
		env_push(shell->env_vars, tmp);
	}
	oldpwd = env_get_by_name(shell->env_vars, "OLDPWD");
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
	oldpwd = env_create_var("OLDPWD", ft_strdup(old_path), true);
	free(old_path);
	free(new_path);
	if (!oldpwd)
		return (CMD_FAILURE);
	env_push(shell->env_vars, oldpwd);
	return (CMD_SUCCESS);
}

int	ft_cd(t_shunting_node *cmd, t_shell *shell, char *new_path)
{
	t_env_var	*tmp;
	char		*old_path;
	char		*curr;

	old_path = getcwd(NULL, 0);
	curr = getcwd(NULL, 0);
	if (cmd->args[0] && cmd->args[1])
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
	if (cmd->args[0] && cmd->args[1])
		return (1);
	if (str_is_equal(cmd->args[0], getcwd(NULL, 0)))
		return (CMD_SUCCESS);
	if (!cmd->args[0] || ((cmd->args)[0] != 0
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
	if ((cmd->args)[1] != 0)
		return (1);
	if (str_is_equal(cmd->args[0], "-") || str_is_equal(cmd->args[0], "--"))
	{
		tmp = env_get_by_name(shell->env_vars, "OLDPWD");
		if (!tmp)
			return (1);
		new_path = tmp->value;
	}
	else
		old_path = getcwd(NULL, 0);
	free(curr);
	if (str_is_equal(cmd->args[0], "..") && str_is_equal(curr, "/"))
		return (set_pwd(shell, old_path));
	if (!new_path || chdir(new_path) == -1)
	{
		echo_err(new_path);
		return (CMD_FAILURE);
	}
	if (str_is_equal(cmd->args[0], "-"))
		printf("~%s\n", new_path);
	return (set_pwd(shell, old_path));
}
