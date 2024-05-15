/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_commands2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:52:13 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/15 16:20:28 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	env_args = ft_malloc((len + 2) * sizeof(char *));
	if (!env_args)
		return (NULL);
	env_args[0] = ft_strdup(cmd);
	i = -1;
	while (++i < len)
		env_args[i + 1] = ft_strdup(args[i]);
	env_args[len + 1] = NULL;
	return (env_args);
}

int	execute_child_process(char *cmd_path, char **args,
	char *command, t_shell *shell)
{
	char	**env_args;
	char	**envp;

	envp = env_to_envp(shell->env_vars);
	if (!envp)
		return (0);
	if (args[0] == NULL)
	{
		if (execve(cmd_path, (char *[]){command, NULL}, envp) == -1)
			return (0);
	}
	else
	{
		env_args = make_env_args(command, args);
		if (!env_args)
			return (0);
		if (execve(cmd_path, env_args, envp) == -1)
		{
			perror("Command failed to execute");
			return (-1);
		}
	}
	return (1);
}

int	execute(char *cmd_path, char **args, char *command, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork failed");
		return (-1);
	}
	else if (pid == 0)
	{
		if (execute_child_process(cmd_path, args, command, shell) <= 0)
			exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
	*shell->exit_status = WEXITSTATUS(status);
	return (WEXITSTATUS(status));
}
