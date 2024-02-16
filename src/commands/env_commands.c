/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:49:54 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/16 09:58:30 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**make_env_args(char *cmd, char **args)
{
	char	**new_arr;
	int		arr_len;
	int		i;

	i = -1;
	arr_len = ft_strlen(args);
	new_arr = malloc((arr_len + 2) * sizeof(char *));
	if (!new_arr)
		return (0);
	new_arr[0] = ft_strdup(cmd);
	if (!new_arr[0])
		return (0);
	while (++i < arr_len)
		new_arr[i + 1] = ft_strdup(args[i]);
	new_arr[arr_len + 1] = NULL;
	return (new_arr);
}

int	execute(char *cmd_path, char **args, char *command)
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
			if (execve(cmd_path, (char *[]){command, NULL}, NULL) == -1)
				return (0);
		}
		else
		{
			env_args = make_env_args(command, args);
			printf("env_args[0]: %s\n", env_args[0]);
			if (!env_args)
				return (0);
			if (execve(cmd_path, env_args, NULL) == -1)
				return (0);
		}
	}
	else
		waitpid(pid, &status, 0);
	return (1);
}

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
			if (execute(cmd_path, cmd->args, cmd->command) == 0)
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
		return (1);
	return (0);
}
