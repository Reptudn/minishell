/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:45:05 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/19 10:31:20 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirect_in(t_shunting_node *cmd, t_shell *shell)
{
	int	fd;

	printf("cmd->value: %s\n", cmd->next->value);
	printf("cmd->args[0]: %s\n", cmd->args[0]);
	fd = open(cmd->next->value, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("dsf: %s: %s\n", cmd->args[0], strerror(errno));
		return (CMD_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (CMD_SUCCESS);
}
