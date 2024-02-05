/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:49:54 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/05 13:45:59 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// this function will later be called when the builtin command
// is not found in the command list and the shell will try to
// execute it as an external command
// if that fails, it return error so that it counts as invalid command
// FOR NOW it just prints takes the cmd without args (gotta fork later for 
// env command with return value)
int	run_env_command(t_shell *shell, t_command *cmd)
{
	char	*cmd_path;
	int		i;
	int		ran;

	i = -1;
	ran = 0;
	while (shell->env[++i])
	{
		cmd_path = ft_strjoin(shell->env[i], "/");
		if (!cmd_path)
			return (0);
		cmd_path = ft_strjoin(cmd_path, cmd->command);
		if (!cmd_path)
		{
			free(cmd_path);
			return (0);
		}
		if (access(cmd_path, F_OK) == 0)
		{
			// if (execve(cmd_path, cmd->args, NULL) == -1)
			// 	break ;
			ran = 1;
			printf("RAN: %s/%s%s%s\n", shell->env[i], COLOR_BG_GREEN, cmd->command, COLOR_RESET);
			break ;
		}
		free(cmd_path);
		cmd_path = NULL;
	}
	if (cmd_path)
		free(cmd_path);
	if (ran)
		return (1);
	return (0);
}
