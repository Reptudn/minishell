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
	int 			counter;
	pid_t 			pid;
	int				exit_code;
	char			*temp = ft_calloc(100000, sizeof(char)); // TODO: make this not a set size

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
				int worked = read(fd[counter][0], temp, 99999); // TODO: make this not a set size
				temp[100000] = '\0';
				if (worked == -1)
					ft_putstr_fd("error\n", 1);
				else if (worked == 0)
				{
					ft_putstr_fd("No output from last command\n", 1);
					return (NULL);
				}
				close(fd[counter][0]);
				break ;
			}
		}
	}
	return (temp);
}