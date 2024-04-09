/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:05:13 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 09:20:39 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free (split);
	return (0);
}

void	free_cmds_helper(t_env_var *cmds)
{
	t_env_var	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		free(cmds->name);
		free(cmds->value);
		free(cmds);
		cmds = tmp;
	}
	cmds = NULL;
}
