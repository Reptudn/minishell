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

// TODO: return NULL when failed and empty string when success but no cmd output
// FIXME: exit status doesnt work correctly yet cuz i think this always succeeds here (or the problem is not here but in the run_command function)
char	*run_pipe(t_shell *shell, t_shunting_node **chain)
{
	int				pipe_amount = get_chain_len(chain);
	int				fd[pipe_amount][2];
	int 			counter;
	pid_t 			pid;
	int				exit_code;
	char			*temp = ft_calloc(1000, sizeof(char));

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
			exit_code = run_command(shell, chain[counter]); // TODO: we might need to handle the exit status here
			exit(exit_code);
		}
		else
		{
			close(fd[counter][1]);
			int status;
			waitpid(pid, &status, 0);
			if (counter == pipe_amount - 1)
			{
				int worked = read(fd[counter][0], temp, 999);
				temp[999] = '\0';
				if (worked == -1)
					ft_putstr_fd("error\n", 1);
				else if (worked == 0)
				{
					ft_putstr_fd("No output from last command\n", 1);
					return (NULL);
				}
				else
					printf("temp: %s\n", temp);
				close(fd[counter][0]);
				break;
			}
		}
	}
	// printf("Shell exit status: %d\n", *shell->exit_status); // This is cmd success even if one cmd fails idk if it should be like that?
	return (temp);
}