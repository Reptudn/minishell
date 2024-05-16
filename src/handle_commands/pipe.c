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
	return (run_command(get_shell(), chain[counter]));
}

int	parent(int counter, int *fd[2], pid_t pid[], char **line)
{
	int		m;
	int		bytes_read;
	char	*tmp;
	int		exits;

	close(fd[counter][1]);
	if (counter != 0)
		close(fd[counter - 1][0]);
	printf("pipe amount %d\n", *get_pipe_amount());
	if (counter == *get_pipe_amount() - 1)
	{
		m = -1;
		printf("waiting for pipes to close\n");
		while (++m < *get_pipe_amount())
		{
			printf("waiting for %d\n", m);
			waitpid(pid[m], &exits, 0);
			if (WIFEXITED(exits) != CMD_SUCCESS)
				*get_shell()->exit_status = WEXITSTATUS(exits);
		}
		printf("done waiting\n");
		*line = read_buff(fd[counter]);
		close(fd[counter][0]);
		return (1);
	}
	return (0);
}

char	*pipe_fail(int counter, int ***fd, pid_t **pid)
{
	perror("minishell: pipe");
	while (--counter >= 0)
	{
		close((*fd)[counter][0]);
		close((*fd)[counter][1]);
	}
	return (0);
}

// TODO: fix space being printed when pipe return null
// FIXME: when running echo 42 | echo no | echo smth | grep 42 it says its running the grep but its not really because it shouldnt pinrt anything and give an error and not smth
char	*run_pipe(t_shell *shell, t_shunting_node **chain, int pipe_amount)
{
	int				**fd;
	int				counter;
	pid_t			*pid;
	char			*line;

	counter = -1;
	line = NULL;
	*get_pipe_amount() = pipe_amount;
	if (!setup_pipe(pipe_amount, &fd, &pid))
		return (NULL);
	counter = -1;
	print_cmd_chain(chain);
	while (chain[++counter] && counter <= pipe_amount)
	{
		printf("doing pipe %s\n", chain[counter]->value);
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
