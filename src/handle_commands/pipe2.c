/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:03:33 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/14 11:11:07 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*read_buff(int fd[2])
{
	int		bytes_read;
	char	buffer[PIPE_BUFFER_SIZE];
	char	*tmp;
	char	*line;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	bytes_read = read(fd[0], buffer, sizeof(buffer) - 1);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(line, buffer);
		free(line);
		if (!tmp)
			return (NULL);
		line = tmp;
		bytes_read = read(fd[0], buffer,
				sizeof(buffer) - 1);
	}
	return (line);
}

int	get_chain_len(t_shunting_node **chain)
{
	int				pipe_amount;

	pipe_amount = 0;
	while (chain[pipe_amount])
		pipe_amount++;
	return (pipe_amount);
}

int	setup_pipe(int pipe_amount, int ***fd, pid_t **pid)
{
	int		counter;

	counter = -1;
	*pid = (pid_t *)ft_calloc(pipe_amount, sizeof(pid_t));
	if (!*pid)
		return (0);
	*fd = (int **)ft_calloc(pipe_amount, sizeof(int *));
	if (!fd)
	{
		free(pid);
		return (0);
	}
	while (++counter < pipe_amount)
	{
		(*fd)[counter] = (int *)ft_calloc(2, sizeof(int));
		if (!((*fd)[counter]))
		{
			while (--counter >= 0)
				free((*fd)[counter]);
			free(*fd);
			free(*pid);
			return (0);
		}
	}
	return (1);
}

char	*complete_pipe(int ***fd, int pipe_amount, char *line)
{
	while (--pipe_amount >= 0)
	{
		close((*fd)[pipe_amount][0]);
		close((*fd)[pipe_amount][1]);
		free((*fd)[pipe_amount]);
	}
	free(*fd);
	return (line);
}
