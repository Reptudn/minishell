/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:45:05 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/21 08:54:32 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirect_out(t_shunting_node *cmd, t_shunting_node *cmd2, t_shell *shell)
{
	int fd;
	int i;

	fd = open(cmd2->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("minishell: %s: %s\n", cmd2->value, strerror(errno));
		return (CMD_FAILURE);
	}
	i = -1;
	while (cmd->args && cmd->args[++i])
	{
		if (write(fd, cmd->args[i], ft_strlen(cmd->args[i])) < 0)
		{
			printf("minishell: %s: %s\n", cmd2->value, strerror(errno));
			close(fd);
			return (CMD_FAILURE);
		}
		if (write(fd, " ", 1) < 0)
		{
			printf("minishell: %s: %s\n", cmd2->value, strerror(errno));
			close(fd);
			return (CMD_FAILURE);
		}
	}
	close(fd);
	return (CMD_SUCCESS);
}
