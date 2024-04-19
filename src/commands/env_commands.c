/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:49:54 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 13:40:33 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

int		execute(char *cmd_path, char **args, char *command, t_shell *shell);
int		execute_child_process(char *cmd_path, char **args, char *command,
			t_shell *shell);
char	**make_env_args(char *cmd, char **args);

char	*create_cmd_path(char *path, char *cmd)
{
	char	*cmd_path;
	char	*temp_cmd_path;

	cmd_path = ft_strjoin(path, "/");
	if (!cmd_path)
		return (NULL);
	temp_cmd_path = ft_strjoin(cmd_path, cmd);
	free(cmd_path);
	if (!temp_cmd_path)
	{
		free(temp_cmd_path);
		return (NULL);
	}
	return (temp_cmd_path);
}

char	*get_env_path_to_cmd(t_shell *shell, char *cmd)
{
	int			i;
	char		*cmd_path;
	t_env_var	*path;
	char		**split;

	i = -1;
	path = env_get_by_name(shell->env_vars, "PATH");
	if (!path)
		return (NULL);
	split = ft_split(path->value, ':');
	while (split[++i])
	{
		cmd_path = create_cmd_path(split[i], cmd);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		cmd_path = NULL;
	}
	return (NULL);
}

int	execute_command(t_shell *shell, t_shunting_node *cmd, char *cmd_path)
{
	int	ran;

	ran = 0;
	if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
	{
		if (execute(cmd_path, cmd->args, cmd->value, shell) == 0)
			return (CMD_FAILURE);
		ran = 1;
	}
	return (ran);
}

int	norm_conform_function_to_return_correct_val(int ran, t_shell *shell)
{
	if (ran)
	{
		if (*shell->exit_status == 512)
			return (2);
		return (CMD_SUCCESS);
	}
	return (CMD_FAILURE);
}

int	run_env_command(t_shell *shell, t_shunting_node *cmd)
{
	char	*cmd_path;
	int		i;
	int		ran;
	char	**path;

	i = -1;
	path = env_get_path(shell->env_vars);
	if (!path)
		return (CMD_FAILURE);
	while (path[++i])
	{
		cmd_path = create_cmd_path(path[i], cmd->value);
		if (!cmd_path)
			return (CMD_FAILURE);
		ran = execute_command(shell, cmd, cmd_path);
		free(cmd_path);
		cmd_path = NULL;
		if (ran)
			break ;
	}
	free_split(path);
	return (norm_conform_function_to_return_correct_val(ran, shell));
}
