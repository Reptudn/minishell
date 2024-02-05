/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:30:38 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/05 09:31:07 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	command_hanlder(t_command *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->command, "cd", 2) == 0)
		return (cd(cmd, shell));
	if (ft_strncmp(cmd->command, "pwd", 3) == 0)
		return (pwd());
	if (ft_strncmp(cmd->command, "echo", 4) == 0)
		return (ft_echo(cmd));
	return (0);
}
