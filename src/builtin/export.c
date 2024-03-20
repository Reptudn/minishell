/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:35:05 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/20 09:41:34 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_export(t_shell *shell, t_shunting_node *cmd)
{
	int			i;
	t_env_var	*env;
	char		**split;

	i = -1;
	split = split_first_occ(cmd->args[0], '=');
	if (!split)
		return (CMD_FAILURE);
	env = env_create_var(split[0], split[1], true);
	free_split(split);
	if (!env)
		return (CMD_FAILURE);
	env_push(shell->env_vars, env);
	return (CMD_SUCCESS);
}
