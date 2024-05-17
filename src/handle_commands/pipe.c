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

#include "../../include/minishell.h"

char	*complete_pipe(int ***fd, int pipe_amount, char *line);
int		get_chain_len(t_shunting_node **chain);
void	print_cmd_chain(t_shunting_node **chain);
char	*read_buff(int fd[2]);
int		setup_pipe(int pipe_amount, int ***fd, pid_t **pid);

int	*get_pipe_amount(void)
{
	static int	pipe_amount = 0;

	return (&pipe_amount);
}

int	child(int counter, int pipe_amount, int *fd[2],
	t_shunting_node **chain)
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
	exit (run_command(get_shell(), chain[counter]));
}

int	parent(int counter, int *fd[2], pid_t pid[], char **line)
{
	int		m;
	int		exits;

	close(fd[counter][1]);
	if (counter != 0)
		close(fd[counter - 1][0]);
	if (counter == *get_pipe_amount() - 1)
	{
		m = -1;
		*get_shell()->exit_status = 0;
		while (++m <= *get_pipe_amount())
		{
			waitpid(pid[m], &exits, 0);
			if (WEXITSTATUS(exits) != 0)
				*get_shell()->exit_status = WEXITSTATUS(exits) % 256;
		}
		*line = read_buff(fd[counter]);
		close(fd[counter][0]);
		return (1);
	}
	return (0);
}

char	*pipe_fail(int counter, int ***fd, pid_t **pid)
{
	(void)pid;
	perror("minishell: pipe");
	while (--counter >= 0)
	{
		close((*fd)[counter][0]);
		close((*fd)[counter][1]);
	}
	return (0);
}

char	*run_pipe(t_shell *shell, t_shunting_node **chain, int pipe_amount)
{
	int				**fd;
	int				counter;
	pid_t			*pid;
	char			*line;

	(void)shell;
	counter = -1;
	line = NULL;
	*get_pipe_amount() = pipe_amount;
	if (!setup_pipe(pipe_amount, &fd, &pid))
		return (NULL);
	counter = -1;
	while (chain[++counter] && counter <= pipe_amount)
	{
		if (pipe(fd[counter]) == -1)
			return (pipe_fail(counter, &fd, &pid));
		pid[counter] = fork();
		if (pid[counter] == -1)
			return (NULL);
		else if (pid[counter] == 0)
			exit(child(counter, pipe_amount, fd, chain));
		else if (parent(counter, fd, pid, &line))
			break ;
	}
	return (complete_pipe(&fd, pipe_amount, line));
}
