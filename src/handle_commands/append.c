/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:29:24 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 15:22:21 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	openfiles(t_shunting_node **chain, int append_amount, int *i, int fd)
{
	*i = 1;
	while (chain[*i] && *i < append_amount - 1)
	{
		fd = open(chain[(*i)++]->value, O_CREAT, 0644);
		if (fd == -1)
		{
			perror("minishell");
			return (CMD_FAILURE);
		}
		close(fd);
	}
	return (CMD_SUCCESS);
}

int	run_append(t_shell *shell, t_shunting_node **chain, int append_amount)
{
	int	fd;
	int	i;
	int	saved_stdout;

	i = 1;
	saved_stdout = dup(STDOUT_FILENO);
	fd = 0;
	if (openfiles(chain, append_amount, &i, fd) == CMD_FAILURE)
		return (CMD_FAILURE);
	if (chain[i] && i == append_amount - 1)
	{
		fd = open(chain[i]->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			perror("minishell");
		if (fd == -1)
			return (CMD_FAILURE);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (CMD_FAILURE);
		run_command(shell, chain[0]);
		close(fd);
	}
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		return (CMD_FAILURE);
	close(saved_stdout);
	return (CMD_SUCCESS);
}
