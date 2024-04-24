/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:48:04 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/24 09:31:07 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_cmd_chain(t_shunting_node **chain);

int	run_delimiter_helper2(int pipefd[2], t_shunting_node **chain,
		char *heredoc, int counter)
{
	char	*temp;
	char	*new_heredoc;

	while (1)
	{
		temp = get_input("heredoc> ");
		if (!temp)
			return (CMD_FAILURE);
		temp = get_var_str(temp);
		if (chain[counter] && str_is_equal(temp, (chain[counter])->value))
			counter++;
		if (chain[counter] == NULL)
			free(temp);
		if (chain[counter] == NULL)
			return (CMD_SUCCESS);
		new_heredoc = ft_strjoin(heredoc, temp);
		free(heredoc);
		heredoc = ft_strjoin(new_heredoc, "\n");
		free(new_heredoc);
		write(pipefd[1], temp, strlen(temp));
		write(pipefd[1], "\n", 1);
		free(temp);
	}
	free(heredoc);
	return (CMD_SUCCESS);
}

int	run_delimiter_helper(int pipefd[2], t_shunting_node **chain)
{
	char	*heredoc;
	int		counter;
	int		exit_status;

	heredoc = malloc(sizeof(char) * 100);
	heredoc[0] = '\0';
	counter = 1;
	exit_status = run_delimiter_helper2(pipefd, chain, heredoc, counter);
	return (exit_status);
}

char	*run_delimiter(t_shunting_node **chain, t_shell *shell)
{
	char	*buffer;
	pid_t	pid;
	int		status;
	int		pipefd[2];
	int		pipefd_back[2];

	buffer = ft_calloc(100000, sizeof(char));
	pipe(pipefd);
	pipe(pipefd_back);
	*chain[0]->exit_status = run_delimiter_helper(pipefd, chain);
	close(pipefd[1]);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		dup2(pipefd_back[1], STDOUT_FILENO);
		*chain[0]->exit_status = run_command(shell, chain[0]);
		close(pipefd_back[0]);
		exit(*chain[0]->exit_status);
	}
	waitpid(pid, &status, 0);
	close(pipefd[1]);
	read(pipefd_back[0], buffer, 99999);
	return (ft_strtrim(buffer, "\n"));
}
