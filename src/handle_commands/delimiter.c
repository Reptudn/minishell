/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:00:27 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/26 12:00:38 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_delimiter(t_shell *shell, t_command *cmd1, t_command *cmd2)
{
	int	status;

	status = CMD_SUCCESS;
	printf("delimiter\n");
	return (status);
}