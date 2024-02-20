/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:29:24 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/20 12:35:55 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_append(t_shell *shell, t_command *cmd1, t_command *cmd2)
{
	int	status;

	status = CMD_SUCCESS;
	printf("append aka heredoc\n");
	return (status);
}
