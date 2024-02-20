/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:53:46 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/20 12:10:03 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

int	run_and(t_shell *shell, t_command *cmd1, t_command *cmd2)
{
	int	status;

	status = run_command(shell, cmd1);
	if (status == CMD_SUCCESS)
		status = run_command(shell, cmd2);
	return (status);
}
