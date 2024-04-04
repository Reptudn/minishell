/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:45:05 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 15:22:24 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirect_out(t_shell *shell, t_shunting_node **chain, int redirection_amout)
{
	int	fd;
	int	i;
	int	saved_stdout;

	i = 0;
	saved_stdout = dup(STDOUT_FILENO);
	while (chain[i] && i < redirection_amout - 1)
	{
		fd = open(chain[i++]->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (CMD_FAILURE);
		close(fd);
	}
	if (chain[i] && i == redirection_amout - 1)
	{
		fd = open(chain[i]->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
