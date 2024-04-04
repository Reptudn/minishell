/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:20:58 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 11:43:03 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*run_pipe(t_shell *shell, t_shunting_node **chain, int counter,
	int pipe_amount, char *str)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;
	char	buffer[10000];
	int		numread;
	char	*result;
	char	*recursive_result;

	if (counter == pipe_amount)
		return (str);
	if (pipe(pipefd) == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		run_command(shell, chain[counter]);
		close(pipefd[0]);
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		numread = read(pipefd[0], buffer, sizeof(buffer) - 1);
		if (numread >= 0)
			buffer[numread] = '\0';
		close(pipefd[0]);
		close(pipefd[1]);
		result = malloc(strlen(str) + strlen(buffer) + 1);
		ft_strncpy(result, str, ft_strlen(str));
		ft_strlcat(result, buffer, sizeof(result) + sizeof(buffer) + 1);
		recursive_result = run_pipe(shell, chain, counter + 1, pipe_amount,
				result);
		free(result);
		return (recursive_result);
	}
	return (NULL);
}
