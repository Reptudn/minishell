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
	temp_cmd_path = ft_strjoin(cmd_path, cmd);;
	if (!temp_cmd_path)
		return (NULL);
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
		cmd_path = NULL;
	}
	return (NULL);
}

int	execute_command(t_shell *shell, t_shunting_node *cmd,
		char *cmd_path, int *status)
{
	int	ran;

	ran = 0;
	if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
	{
		*status = execute(cmd_path, cmd->args, cmd->value, shell);
		if (*status == -1)
			return (-1);
		ran = 1;
	}
	return (ran);
}

int	norm_conform_function_to_return_correct_val(int ran, int status,
	char *val)
{
	if (ran && val && (*val != '.' && *val != '/'))
		return (127);
	else if (ran)
		return (status);
	return (-1);
}

int	run_env_command(t_shell *shell, t_shunting_node *cmd)
{
	char	*cmd_path;
	int		i;
	int		ran;
	char	**path;
	int		status;

	i = -1;
	path = env_get_path(shell->env_vars);
	if (!path)
		return (-1);
	ran = 0;
	while (path[++i] && (cmd->value[0] != '.' && cmd->value[1] != '/'))
	{
		cmd_path = create_cmd_path(path[i], cmd->value);
		if (!cmd_path)
			return (-1);
		ran = execute_command(shell, cmd, cmd_path, &status);
		cmd_path = NULL;
		if (ran)
			break ;
	}
	free_split(path);
	return (norm_conform_function_to_return_correct_val(ran, status,
			cmd->value));
}
