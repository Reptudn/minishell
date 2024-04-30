/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:35:05 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/25 12:32:28 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_export(t_env_var *env);
int	export_error(char *arg);

bool	is_valid_var_indentifier(char *arg)
{
	int	i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (false);
	i = 0;
	while (arg[++i])
	{
		if (arg[i] == '+' && arg[i + 1] == 0)
			return (true);
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (false);
	}
	return (true);
}

int	handle_no_equal(t_shell *shell, char *arg)
{
	t_env_var	*env;

	if (!is_valid_var_indentifier(arg))
		return (export_error(arg));
	env = env_get_by_name(shell->env_vars, arg);
	if (!env)
	{
		env = env_create_var(arg, NULL, false);
		if (!env)
			return (CMD_FAILURE);
		env_push(shell->env_vars, env);
	}
	else
	{
		free(env->value);
		env->value = NULL;
	}
	return (CMD_SUCCESS);
}

int	replace_existing_val(char **split, t_env_var *env, bool append)
{
	char		*old;

	if (!append)
		free(env->value);
	old = env->value;
	if (split[1] && !append)
		env->value = ft_strdup(split[1]);
	else if (split[1] && append)
		env->value = ft_strjoin(env->value, split[1]);
	else
		env->value = ft_strdup("");
	if (append)
		free(old);
	free_split(split);
	return (CMD_SUCCESS);
}

int	create_env_var(char **split, t_shell *shell)
{
	t_env_var	*env;

	if (split[1])
		env = env_create_var(split[0], split[1], false);
	else
		env = env_create_var(split[0], ft_strdup(""), false);
	free_split(split);
	if (!env)
		return (CMD_FAILURE);
	env_push(shell->env_vars, env);
	return (CMD_SUCCESS);
}

int	handle_arg(t_shell *shell, char *arg)
{
	char		**split;
	t_env_var	*env;
	bool		append;

	if (arg[0] == '=')
		return (export_error(arg));
	if (!ft_strchr(arg, '='))
		return (handle_no_equal(shell, arg));
	split = split_first_occ(arg, '=');
	if (!split)
		return (CMD_FAILURE);
	if (!is_valid_var_indentifier(split[0]))
	{
		free_split(split);
		return (export_error(arg));
	}
	append = false;
	if (split[0][ft_strlen(split[0]) - 1] == '+')
	{
		split[0][ft_strlen(split[0]) - 1] = 0;
		append = true;
	}
	env = env_get_by_name(shell->env_vars, split[0]);
	if (env)
	{
		replace_existing_val(split, env, append);
		return (CMD_SUCCESS);
	}
	return (create_env_var(split, shell));
}

int	ft_export(t_shell *shell, t_shunting_node *cmd)
{
	int	i;
	int	status;

	if (!cmd->args || !cmd->args[0])
		return (print_export(shell->env_vars));
	i = -1;
	while (cmd->args && cmd->args[++i])
	{
		status = handle_arg(shell, cmd->args[i]);
		if (status != CMD_SUCCESS)
			return (status);
	}
	return (CMD_SUCCESS);
}
