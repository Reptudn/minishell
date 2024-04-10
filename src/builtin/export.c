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

void	print_export(t_env_var *env)
{
	while (env)
	{
		if (env->value[0] == '\0')
			printf("declare -x %s\n", env->name);
		else
			printf("declare -x %s=\"%s\"\n", env->name, env->value);
		env = env->next;
	}
}

// TODO: check if this is really like in bash now
int	ft_export(t_shell *shell, t_shunting_node *cmd)
{
	t_env_var	*env;
	char		**split;
	int			i;

	if (!cmd->args || !cmd->args[0])
	{
		print_export(shell->env_vars);
		return (CMD_SUCCESS);
	}
	i = -1;
	while (cmd->args && cmd->args[++i])
	{
		if (cmd->args[i][0] == '=')
		{
			ft_putstr_fd("minishell: export: `=': not a valid identifier\n", 2);
			return (CMD_FAILURE);
		}
		if (!ft_strchr(cmd->args[i], '='))
		{
			env = env_get_by_name(shell->env_vars, cmd->args[i]);
			if (!env)
			{
				env = env_create_var(cmd->args[i], ft_strdup(""), false);
				if (!env)
					return (CMD_FAILURE);
				env_push(shell->env_vars, env);
			}
			continue ;
		}
		split = split_first_occ(cmd->args[i], '=');
		if (!split)
			return (CMD_FAILURE);
		env = env_get_by_name(shell->env_vars, split[0]);
		if (env)
		{
			free(env->value);
			if (split[1])
				env->value = ft_strdup(split[1]);
			else
				env->value = ft_strdup("");
			free_split(split);
			continue ;
		}
		if (split[1])
			env = env_create_var(split[0], split[1], false);
		else
			env = env_create_var(split[0], ft_strdup(""), false);
		free_split(split);
		if (!env)
			return (CMD_FAILURE);
		env_push(shell->env_vars, env);
	}
	return (CMD_SUCCESS);
}

// int	ft_export(t_shell *shell, t_shunting_node *cmd)
// {
// 	t_env_var	*env;
// 	char		**split;

// 	if (!cmd->args || !cmd->args[0])
// 	{
// 		print_export(shell->env_vars);
// 		return (CMD_SUCCESS);
// 	}
// 	split = split_first_occ(cmd->args[0], '=');
// 	if (!split)
// 		return (CMD_FAILURE);
// 	env = env_get_by_name(shell->env_vars, split[0]);
// 	if (env)
// 	{
// 		free(env->value);
// 		if (split[1])
// 			env->value = ft_strdup(split[1]);
// 		else
// 			env->value = ft_strdup("");
// 		free_split(split);
// 		return (CMD_SUCCESS);
// 	}
// 	if (split[1])
// 		env = env_create_var(split[0], split[1], false);
// 	else
// 		env = env_create_var(split[0], ft_strdup(""), false);
// 	free_split(split);
// 	if (!env)
// 		return (CMD_FAILURE);
// 	env_push(shell->env_vars, env);
// 	return (CMD_SUCCESS);
// }
