/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:32:55 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/20 11:10:09 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_path_to_cmd(t_shell *shell, char *cmd);
char	**make_env_args(char *cmd, char **args);
int		execute(char *cmd_path, char **args, char *command, t_shell *shell);

int	run_path_command(t_shell *shell, t_command *cmd)
{
	if (access(cmd->command, F_OK) != 0)
	{
		// printf("minishell: %s: No such file or directory\n", cmd->command);
		return (CMD_FAILURE);
	}
	if (access(cmd->command, X_OK) != 0)
	{
		// printf("minishell: %s: Permission denied\n", cmd->command);
		return (CMD_FAILURE);
	}
	if (execute(cmd->command, cmd->args, cmd->command, shell))
		return (CMD_SUCCESS);
	return (CMD_FAILURE);
}
