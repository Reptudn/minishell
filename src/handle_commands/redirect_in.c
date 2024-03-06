/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:45:05 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/06 09:44:04 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirect_in(t_command *cmd, t_shell *shell)
{
	int	fd;

	fd = open(cmd->args[0], O_RDONLY);
	if (fd == -1)
	{
		printf("minishell: %s: %s\n", cmd->args[0], strerror(errno));
		return (CMD_FAILURE);
	}
	dup2(fd, 0);
	close(fd);
	return (run_command(shell, cmd->next));
}
