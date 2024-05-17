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

int		set_pwd_helper(t_env_var *tmp, t_env_var *oldpwd,
			char *new_path, char *old_path);
void	set_pwd_helper_helper_fuck_norminette(char *new_path, char *old_path);
int		set_pwd_helper2(t_env_var *oldpwd, char *old_path,
			char *new_path, t_shell *shell);
char	*handle_home_path(t_shunting_node *cmd, t_shell *shell, char *new_path);
int		handle_same_path(t_shunting_node *cmd, char *old_path);
char	*ft_getcwd(char *str, int num);

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
	if (set_pwd_helper(tmp, oldpwd, new_path, old_path))
		return (CMD_FAILURE);
	oldpwd = env_get_by_name(shell->env_vars, "OLDPWD");
	if (set_pwd_helper2(oldpwd, old_path, new_path, shell))
		return (CMD_FAILURE);
	if (!oldpwd)
		return (CMD_FAILURE);
	return (CMD_SUCCESS);
}

int	handle_too_many_args(t_shunting_node *cmd, char *old_path)
{
	if (cmd->args && cmd->args[0] && cmd->args[1])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (CMD_FAILURE);
	}
	return (CMD_SUCCESS);
}

char	*handle_old_path(t_shunting_node *cmd, t_shell *shell,
	char *old_path, char *new_path)
{
	t_env_var	*tmp;

	if (str_is_equal(cmd->args[0], "-") || str_is_equal(cmd->args[0], "--"))
	{
		tmp = env_get_by_name(shell->env_vars, "OLDPWD");
		if (!tmp)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
			return (NULL);
		}
		new_path = tmp->value;
	}
	return (new_path);
}

int	ft_cd(t_shunting_node *cmd, t_shell *shell, char *new_path)
{
	char		*old_path;

	old_path = ft_getcwd(NULL, 0);
	if (handle_too_many_args(cmd, old_path) == CMD_FAILURE)
		return (CMD_FAILURE);
	if (handle_same_path(cmd, old_path) == CMD_SUCCESS)
		return (CMD_SUCCESS);
	new_path = handle_home_path(cmd, shell, new_path);
	new_path = handle_old_path(cmd, shell, old_path, new_path);
	if (str_is_equal(cmd->args[0], "..") && str_is_equal(old_path, "/"))
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
