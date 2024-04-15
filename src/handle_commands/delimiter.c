/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:48:04 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/15 08:14:27 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_cmd_chain(t_shunting_node **chain);

char	*run_delimiter(t_shunting_node **chain, t_shell *shell)
{
	char	*heredoc;
	char	*new_heredoc;
	char	*temp;
	int		exit_status;
	int		counter;
	int		pipefd[2];
	char	*buffer = ft_calloc(100000, sizeof(char));
	pid_t	pid;
	int		status;

	heredoc = malloc(sizeof(char) * 100);
	heredoc[0] = '\0';
	counter = 1;
	pipe(pipefd);
	while (1)
	{
		temp = readline("heredoc> ");
		if (!temp)
		{
			exit_status = CMD_FAILURE;
			break ;
		}
		if (chain[counter] && str_is_equal(temp, (chain[counter])->value))
			counter++;
		if (chain[counter] == NULL)
		{
			exit_status = CMD_SUCCESS;
			free(temp);
			break ;
		}
		new_heredoc = ft_strjoin(heredoc, temp);
		free(heredoc);
		heredoc = ft_strjoin(new_heredoc, "\n");
		free(new_heredoc);
		write(pipefd[1], temp, strlen(temp));
		write(pipefd[1], "\n", 1);
		free(temp);
	}
	close(pipefd[1]);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		exit_status = run_command(shell, chain[counter]);
		close(pipefd[0]);
		exit(exit_status);
	}
	else
	{
		waitpid(pid, &status, 0);
		read(pipefd[0], buffer, sizeof(buffer));
	}
	*chain[0]->exit_status = exit_status;
	printf("-- buffer --\n%s\n-- buffer --", buffer);
	return (strdup(buffer));
}
// TODO: i think heredoc is not freed in the end <- YES THATS TRUE
// FIXME: the buffer in the end has to be sent to chain[0] and be executed and that result has to be returned
// -> the buffer needs to be reirected to stdin when the chain[0] cmd is executed