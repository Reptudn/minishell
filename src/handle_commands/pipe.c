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

int	fuck_around_and_find_out_how_many_pipes(t_shunting_node **chain)
{
	int				pipe_amount;
	t_shunting_node	*current;

	current = *chain;
	pipe_amount = 0;
	while (current->next != NULL)
	{
		pipe_amount++;
		current = current->next;
	}
	while (current->prev != NULL)
		current = current->prev;
	return (pipe_amount);
}

char	*run_pipe(t_shell *shell, t_shunting_node **chain)
{
	int				pipe_amount = fuck_around_and_find_out_how_many_pipes(chain);
	int				fd[pipe_amount][2];
	int 			counter;
	pid_t 			pid;
	t_shunting_node *current = *chain;
	for (; current != NULL; current = current->next) {
		printf("chain->value: %s", current->value);
	}

	//fd[0] == read end
	//fd[1] == write end
	//dup2(to where, from where);
	counter = 0;
	current = *chain;
	while (counter <= pipe_amount)
	{
		if (pipe(fd[counter]) == -1)
			return (NULL);
		pid = fork();
		if (pid == -1)
			return (NULL);
		else if (pid == 0)
		{
			if (counter != 0) // not the first command
			{
				close(fd[counter - 1][1]); // Close the write end of the previous pipe
				dup2(fd[counter - 1][0], STDIN_FILENO); // Redirect stdin to the read end of the previous pipe
			}
			if (counter != pipe_amount) // not the last command
			{
				close(fd[counter][0]); // Close the read end of the current pipe
				dup2(fd[counter][1], STDOUT_FILENO); // Redirect stdout to the write end of the current pipe
			}
			run_command(shell, current);
			exit(CMD_SUCCESS);
		}
		else
		{
			if (counter == pipe_amount) // last cmd can read from it
			{
				char *temp = malloc(1000);
				int worked = 0;
				worked = read(fd[counter][0], temp, 999);
				if (worked == -1)
					printf("error\n");
				temp[1000] = '\0';
				printf("temp: %s\n", temp);
			}
		}
		counter++;
		current = current->next;
	}
	// close the read and write ends of the last pipe in the parent process
	close(fd[pipe_amount][0]);
	close(fd[pipe_amount][1]);
	return (NULL);
}

/*


	echo hello         dup2(pipefd[0], STDIN_FILENO);  close(pipefd[0]); close(pipefd[1]);


	wc -l              dup2(pipefd[1], 1); close(pipefd[0]); close(pipefd[1]);






*/