/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:32:55 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/20 09:30:09 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_path_to_cmd(t_shell *shell, char *cmd);
char	**make_env_args(char *cmd, char **args);
int		execute(char *cmd_path, char **args, char *command, t_shell *shell);

int	run_path_command(t_shell *shell, t_shunting_node *cmd)
{
	if (access(cmd->value, F_OK) != 0)
		return (CMD_FAILURE);
	if (access(cmd->value, X_OK) != 0)
	{
		printf("minishell: %s: Permission denied\n", cmd->value);
		return (CMD_IMPROP);
	}
	return (execute(cmd->value, cmd->args, cmd->value, shell));
}
