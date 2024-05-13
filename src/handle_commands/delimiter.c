/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:48:04 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/13 09:52:32 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_cmd_chain(t_shunting_node **chain);
int		run_delimiter_helper2dot1(char *temp, char *heredoc);
int		run_delmiter_im_crying(void);

int	run_delimiter_helper2(int pipefd[2], t_shunting_node **chain,
		char *heredoc, int counter)
{
	char	*temp;
	char	*new_heredoc;

	while (42 == 42)
	{
		temp = get_input("heredoc> ");
		if (!temp && *sigint_recv() && run_delmiter_im_crying())
			return (CMD_FAILURE);
		else if (!temp && !*sigint_recv())
			return (CMD_FAILURE);
		if (chain[counter] && str_is_equal(temp, (chain[counter])->value))
			counter++;
		if (chain[counter] == NULL && run_delimiter_helper2dot1(temp, heredoc))
			return (CMD_SUCCESS);
		new_heredoc = ft_strjoin(heredoc, temp);
		free(heredoc);
		heredoc = ft_strjoin(new_heredoc, "\n");
		free(new_heredoc);
		if (temp)
			write(pipefd[1], temp, strlen(temp));
		write(pipefd[1], "\n", 1);
		free(temp);
	}
	return (CMD_SUCCESS);
}

void	clean_quotes_in_chain(t_shunting_node **chain)
{
	int		i;
	int		j;
	char	*temp;
	char	*temp2;

	i = 0;
	j = 0;
	temp = strdup(chain[1]->value);
	free(chain[1]->value);
	temp2 = (char *)malloc(sizeof(char) * (ft_strlen(temp) + 1));
	if (!temp2)
		printf("malloc failed\n");
	while (temp[i])
	{
		if (temp[i] == '\'' || temp[i] == '\"')
		{
			i++;
			continue ;
		}
		temp2[j++] = temp[i++];
	}
	temp2[j] = '\0';
	free(temp);
	chain[1]->value = strdup(temp2);
}

int	run_delimiter_helper(int pipefd[2],
		t_shunting_node **chain)
{
	char	*heredoc;
	int		counter;
	int		exit_status;

	heredoc = malloc(sizeof(char) * 100);
	heredoc[0] = '\0';
	counter = 1;
	signal_ignore_parent();
	exit_status = run_delimiter_helper2(pipefd, chain, heredoc, counter);
	signal_restore_parent();
	free(heredoc);
	return (exit_status);
}

int	run_delimiter_helper3(pid_t pid, int pipefd[2],
		int pipefd_back[2], t_shunting_node **chain)
{
	t_shell	*shell;

	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		dup2(pipefd_back[1], STDOUT_FILENO);
		*chain[0]->exit_status = run_command(shell, chain[0]);
		close(pipefd_back[0]);
		exit(*chain[0]->exit_status);
	}
	return (0);
}

// FIXME: Double free
char	*run_delimiter(t_shunting_node **chain,
		t_shell *shell)
{
	char	*buffer;
	pid_t	pid;
	int		status;
	int		pipefd[2];
	int		pipefd_back[2];

	buffer = ft_calloc(1000000, sizeof(char));
	pipe(pipefd);
	pipe(pipefd_back);
	*chain[0]->exit_status = run_delimiter_helper(pipefd, chain);
	close(pipefd[1]);
	pid = fork();
	if (run_delimiter_helper3(pid, pipefd, pipefd_back, chain))
		return (NULL);
	waitpid(pid, &status, 0);
	close(pipefd[1]);
	close(pipefd[0]);
	close(pipefd_back[1]);
	read(pipefd_back[0], buffer, 999999);
	return (buffer);
}
