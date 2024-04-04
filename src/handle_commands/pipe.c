/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:20:58 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 14:45:57 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//TODO: Implement pipe handling like bash that means open as much pipes as there are 

char	*run_pipe(t_shell *shell, t_shunting_node **chain, int counter,
	int pipe_amount, char *str)
{
	int		pipefd[2];
	pid_t	pid;
	// int		status;
	char	buffer[10000];
	char	*result;
	// int		numread;
	char	*recursive_result;

	if (counter == pipe_amount)
		return (str);
	if (!counter && pipe(pipefd) == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
	{	if (counter == pipe_amount)
			dup2(pipefd[1], 1);
		run_command(shell, chain[counter]);
		close(pipefd[0]);
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		// waitpid(pid, &status, 0);
		// numread = read(pipefd[0], buffer, sizeof(buffer) - 1);
		// if (numread >= 0)
		// 	buffer[numread] = '\0';
		// printf("buffer: %s\n", buffer);
		dup2(pipefd[0], 0);
		close(pipefd[1]);
		close(pipefd[0]);
		result = malloc(strlen(str) + strlen(buffer) + 1);
		ft_strncpy(result, str, ft_strlen(str));
		ft_strlcat(result, buffer, sizeof(result) + sizeof(buffer) + 1);
		recursive_result = run_pipe(shell, chain, ++counter, pipe_amount,
				result);
		// close(pipefd[0]);
		free(result);
		return (recursive_result);
	}
	return (NULL);
}





/*


	echo hello         dup2(pipefd[0], STDIN_FILENO);  close(pipefd[0]); close(pipefd[1]);


	wc -l              dup2(pipefd[1], 1); close(pipefd[0]); close(pipefd[1]);






*/