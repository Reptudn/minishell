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
	int				pipe_amount = get_chain_len(chain);
	int				fd[pipe_amount][2];
	int				counter;
	pid_t			pid;
	int				exit_code;
	char			*line;

	counter = -1;
	line = NULL;
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
			close(fd[counter][1]);
			int status;
			waitpid(pid, &status, 0); //TODO: fix cat | cat | ls
			if (counter == pipe_amount - 1) //not conform in any way but works
			{
				char buffer[4096]; // buffer to read data in chunks
				ssize_t bytesRead;
				line = malloc(1);  // start with 1 byte
				line[0] = '\0';    // null terminate the string
				while ((bytesRead = read(fd[counter][0], buffer, sizeof(buffer) - 1)) > 0)
				{
					buffer[bytesRead] = '\0'; // null terminate the buffer
					line = realloc(line, strlen(line) + bytesRead + 1); // expand line
					strcat(line, buffer); // append buffer to line
				}
				close(fd[counter][0]);
				break;
			}
		}
	}
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}
