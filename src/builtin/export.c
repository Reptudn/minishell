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
int	export_error(void);

int	handle_no_equal(t_shell *shell, char *arg)
{
	t_env_var	*env;

	env = env_get_by_name(shell->env_vars, arg);
	if (!env)
	{
		env = env_create_var(arg, ft_strdup(""), false);
		if (!env)
			return (CMD_FAILURE);
		env_push(shell->env_vars, env);
	}
	return (CMD_SUCCESS);
}

int	replace_existing_val(char **split, t_env_var *env)
{
	free(env->value);
	if (split[1])
		env->value = ft_strdup(split[1]);
	else
		env->value = ft_strdup("");
	free_split(split);
	return (CMD_SUCCESS);
}

int	create_env_var(char **split, t_shell *shell)
{
	t_env_var	*env;
	// int			i;

	// i = 0;
	if (split[1])
		env = env_create_var(split[0], split[1], false);
	else
		env = env_create_var(split[0], ft_strdup(""), false);
	free(split[0]);
	free(split);
	if (!env)
		return (CMD_FAILURE);
	env_push(shell->env_vars, env);
	return (CMD_SUCCESS);
}

int	handle_arg(t_shell *shell, char *arg)
{
	char		**split;
	t_env_var	*env;

	if (arg[0] == '=')
		return (export_error());
	if (!ft_strchr(arg, '='))
		return (handle_no_equal(shell, arg));
	split = split_first_occ(arg, '=');
	if (!split)
		return (CMD_FAILURE);
	env = env_get_by_name(shell->env_vars, split[0]);
	if (env)
	{
		replace_existing_val(split, env);
		return (CMD_SUCCESS);
	}
	return (create_env_var(split, shell));
}

int	ft_export(t_shell *shell, t_shunting_node *cmd)
{
	int	i;

	if (!cmd->args || !cmd->args[0])
		return (print_export(shell->env_vars));
	i = -1;
	while (cmd->args && cmd->args[++i])
		if (handle_arg(shell, cmd->args[i]) == CMD_FAILURE)
			return (CMD_FAILURE);
	return (CMD_SUCCESS);
}
