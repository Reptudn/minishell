/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:45:05 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 09:15:39 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirect_out(t_shell *shell, t_shunting_node *cmd, t_shunting_node *cmd2,
	int redirection_amout)
{
	int	fd;
	int	i;
	int	saved_stdout;

	i = 1;
	saved_stdout = dup(STDOUT_FILENO);
	while (i <= redirection_amout)
	{
		if (ft_strncmp(cmd2->value, ">", 1) == 0)
		{
			i++;
			cmd2 = cmd2->next;
			continue ;
		}
		fd = open(cmd2->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (CMD_FAILURE);
		close(fd);
		cmd2 = cmd2->next;
	}
	if (i == redirection_amout)
	{
		fd = open(cmd2->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (CMD_FAILURE);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (CMD_FAILURE);
		run_command(shell, cmd);
		close(fd);
	}
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		return (CMD_FAILURE);
	close(saved_stdout);
	return (CMD_SUCCESS);
}
