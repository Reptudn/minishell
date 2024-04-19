/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:48:04 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/19 11:19:13 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_cmd_chain(t_shunting_node **chain);

// TODO: check if exit status is correct here
// FIXME: heredoc works correctly with ctrl + c and ctrl + d when line was exited with ctrl + c exit heredoc with CMD_FAILURE
// FIXME: when ctrl + c/d is pressed we are stuck in the heredoc
char	*run_delimiter(t_shunting_node **chain, t_shell *shell)
{
	char	*heredoc;
	char	*new_heredoc;
	char	*temp;
	int		exit_status;
	int		counter;
	char	*buffer = ft_calloc(100000, sizeof(char));
	pid_t	pid;
	int		status;
	int		pipefd[2];
	int		pipefd_back[2];

	heredoc = malloc(sizeof(char) * 100);
	heredoc[0] = '\0';
	counter = 1;
	pipe(pipefd);
	pipe(pipefd_back);
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
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		dup2(pipefd_back[1], STDOUT_FILENO);
		exit_status = run_command(shell, chain[0]);
		close(pipefd_back[0]);
		exit(exit_status);
	}
	else
	{
		waitpid(pid, &status, 0);
		close(pipefd[1]);
		read(pipefd_back[0], buffer, 99999);
	}
	if (heredoc)
		free(heredoc);
	*chain[0]->exit_status = exit_status;
	return (ft_strdup(buffer));
}
// TODO: i think heredoc is not freed in the end <- YES THATS TRUE
