/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:45:05 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/28 12:20:34 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirect_in(t_shunting_node *cmd, t_shunting_node *cmd2, t_shell *shell)
{
	int	fd;
	int	saved_stdin;

	saved_stdin = dup(0);
	fd = open(cmd2->value, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (CMD_FAILURE);
	}
	if (dup2(fd, 0) == -1)
	{
		perror("dup2");
		return (CMD_FAILURE);
	}
	run_command(shell, cmd);
	dup2(saved_stdin, 0);
	close(fd);
	return (CMD_SUCCESS);
}
