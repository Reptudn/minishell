/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:45:05 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/11 09:54:47 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int redirect_out(t_shunting_node *cmd, t_shell *shell)
{
	// int fd;
	// int i;
	// char *buffer;

	// i = 0;
	// fd = open(cmd->next->command, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// if (fd == -1)
	// {
	// 	printf("minishell: %s: %s\n", cmd->next->command, strerror(errno));
	// 	return (CMD_FAILURE);
	// }
	// //buffer??
	// write (fd, buffer, ft_strlen(buffer));
	// free(buffer);
	// close(fd);
	return (CMD_SUCCESS);
}
