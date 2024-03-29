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

// TODO: Isnt quite like the original bash export command
int	ft_export(t_shell *shell, t_shunting_node *cmd)
{
	t_env_var	*env;
	char		**split;

	split = split_first_occ(cmd->args[0], '=');
	if (!split)
		return (CMD_FAILURE);
	env = env_get_by_name(shell->env_vars, split[0]);
	if (env)
	{
		free(env->value);
		env->value = ft_strdup(split[1]);
		free_split(split);
		return (CMD_SUCCESS);
	}
	env = env_create_var(split[0], split[1], true);
	free_split(split);
	if (!env)
		return (CMD_FAILURE);
	env_push(shell->env_vars, env);
	return (CMD_SUCCESS);
}
