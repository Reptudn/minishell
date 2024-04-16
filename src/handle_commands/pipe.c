/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsabia <nsabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:20:58 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/09 11:50:05 by nsabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_cmd_chain(t_shunting_node **chain);

int	get_chain_len(t_shunting_node **chain)
{
	int				pipe_amount;

	pipe_amount = 0;
	while (chain[pipe_amount])
		pipe_amount++;
	return (pipe_amount);
}

char	*run_pipe(t_shell *shell, t_shunting_node **chain)
{
	int		pipe_amount = get_chain_len(chain);
	int		fd[pipe_amount][2];
	int		counter;
	pid_t	pid;
	pid_t	pids[pipe_amount];
	int		exit_code;
	char	*temp;

	counter = -1;
	temp = NULL;

	counter = -1;
	while (chain[++counter] && counter <= pipe_amount)
	{
		if (pipe(fd[counter]) == -1)
			return (NULL);
		pid = fork();
		if (pid == -1)
			return (NULL);
		else if (pid == 0)
		{
			if (counter != 0)
			{
				close(fd[counter - 1][1]);
				dup2(fd[counter - 1][0], STDIN_FILENO);
			}
			if (counter != pipe_amount)
			{
				close(fd[counter][0]);
				dup2(fd[counter][1], STDOUT_FILENO);
			}
			exit_code = run_command(shell, chain[counter]);
			exit(exit_code);
		}
		else
		{
			pids[counter] = pid;
			if (counter != 0)
				close(fd[counter - 1][0]);
		}
	}
	for (int i = 0; i < pipe_amount; i++)
		close(fd[i][1]);
	for (int i = 0; i <= counter; i++)
	{
		int status;
		waitpid(pids[i], &status, 0);
	}
	char buffer[4096];
	ssize_t bytes_read;
	temp = NULL;
	while ((bytes_read = read(fd[pipe_amount - 1][0], buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		if (temp != NULL)
		{
			char *old_temp = temp;
			temp = ft_strjoin(temp, buffer);
			free(old_temp);
		}
		else
			temp = strdup(buffer);
	}
	close(fd[pipe_amount - 1][0]);
	if (temp && temp[ft_strlen(temp) - 1] == '\n')
		temp[ft_strlen(temp) - 1] = '\0';
	return (temp);
}
