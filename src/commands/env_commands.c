/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:49:54 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/11 10:18:57 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

// this will cause lots of leaks, but for now it's just a test
char	**make_env_args(char *cmd, char **args)
{
	int		len;
	int		i;
	char	**env_args;

	len = 0;
	if (!args)
		return ((char *[]){cmd, NULL});
	while (args[len] != NULL)
		len++;
	env_args = malloc((len + 2) * sizeof(char *));
	if (!env_args)
		return (NULL);
	env_args[0] = strdup(cmd);
	i = -1;
	while (++i < len)
		env_args[i + 1] = strdup(args[i]);
	env_args[len + 1] = NULL;
	return (env_args);
}

int	execute(char *cmd_path, char **args, char *command, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	**env_args;

	pid = fork();
	if (pid < 0)
		return (0);
	else if (pid == 0)
	{
		if (args[0] == NULL)
		{
			if (execve(cmd_path, (char *[]){command, NULL}, shell->envp) == -1)
				return (0);
		}
		else
		{
			env_args = make_env_args(command, args);
			if (!env_args)
				return (0);
			if (execve(cmd_path, env_args, shell->envp) == -1)
			{
				perror("\033[0;31mCommand failed to execute");
				return (-1);
			}
		}
	}
	else
		waitpid(pid, &status, 0);
	return (1);
}

// TODO: check for leaks
char	*get_env_path_to_cmd(t_shell *shell, char *cmd)
{
	int		i;
	char	*cmd_path;

	i = -1;
	while (shell->env[++i])
	{
		cmd_path = ft_strjoin(shell->env[i], "/");
		if (!cmd_path)
			return (0);
		cmd_path = ft_strjoin(cmd_path, cmd);
		if (!cmd_path)
		{
			free(cmd_path);
			return (0);
		}
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		cmd_path = NULL;
	}
	return (NULL);
}

// this function will later be called when the builtin command
// is not found in the command list and the shell will try to
// execute it as an external command
// if that fails, it return error so that it counts as invalid command
// FOR NOW it just prints takes the cmd without args (gotta fork later for 
// env command with return value)
int	run_env_command(t_shell *shell, t_shunting_node *cmd)
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
		cmd_path = ft_strjoin(cmd_path, cmd->value);
		if (!cmd_path)
		{
			free(cmd_path);
			return (0);
		}
		if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
		{
			if (execute(cmd_path, cmd->args, cmd->value, shell) == 0)
				break ;
			ran = 1;
			break ;
		}
		free(cmd_path);
		cmd_path = NULL;
	}
	if (cmd_path)
		free(cmd_path);
	if (ran)
		return (CMD_SUCCESS);
	return (CMD_FAILURE);
}
