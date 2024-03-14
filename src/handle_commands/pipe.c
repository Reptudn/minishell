/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:20:58 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/14 09:02:29 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_pipe_cmd(t_shunting_node *cmd1, t_shunting_node *cmd2, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	status = CMD_SUCCESS;
	if (pipe(fd) == -1)
		return (CMD_FAILURE);
	pid = fork();
	if (pid < 0)
		return (CMD_FAILURE);
	else if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		if (run_command(shell, cmd1) == CMD_FAILURE)
		{
			printf("pipe1: %s: %s\n", cmd1->args[0], strerror(errno));
			return (CMD_FAILURE);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		if (run_command(shell, cmd2) == CMD_FAILURE)
		{
			printf("pipe2: %s: %s\n", cmd2->args[0], strerror(errno));
			return (CMD_FAILURE);
		}
	}
	printf("pipe succesful\n");
	return (CMD_SUCCESS);
}
