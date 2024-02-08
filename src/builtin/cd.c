/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:21:48 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/08 09:56:58 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cd(t_command *cmd, t_shell *shell)
{
	char	*new_path;

	if ((cmd->args)[1] != 0)
	{
		printf("cd: too many arguments\n");
		return (0);
	}
	new_path = (cmd->args)[0];
	if (chdir(new_path) == -1)
	{
		printf("cd: %s: %s\n", new_path, strerror(errno));
		return (0);
	}
	free(shell->path);
	shell->path = getcwd(NULL, 0);
	return (1);
}
