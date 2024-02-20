/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:56:52 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/20 10:57:49 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_or(t_shell *shell, t_command *cmd1, t_command *cmd2)
{
	int	status;

	status = run_command(shell, cmd1);
	if (status == CMD_FAILURE)
		status = run_command(shell, cmd2);
	return (status);
}
