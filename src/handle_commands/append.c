/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:29:24 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 09:11:15 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_append(t_shell *shell, t_shunting_node *cmd1, t_shunting_node *cmd2,
	int append_amount)
{
	int	fd;
	int	i;
	int	saved_stdout;

	i = 1;
	saved_stdout = dup(STDOUT_FILENO);
	while (i <= append_amount)
	{
		if (ft_strncmp(cmd2->value, ">>", 1) == 0)
		{
			i++;
			cmd2 = cmd2->next;
			continue ;
		}
		fd = open(cmd2->value, O_CREAT, 0644);
		if (fd == -1)
			return (CMD_FAILURE);
		close(fd);
		cmd2 = cmd2->next;
	}
	if (i == append_amount)
	{
		fd = open(cmd2->value, O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
			return (CMD_FAILURE);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (CMD_FAILURE);
		run_command(shell, cmd1);
		printf("\n");
		close(fd);
	}
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		return (CMD_FAILURE);
	close(saved_stdout);
	return (CMD_SUCCESS);
}
