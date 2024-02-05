/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:30:38 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/05 14:07:22 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	command_handler(t_shell *shell, char *line)
{
	t_command	*cmds;
	int			i;

	cmds = make_cmds(line, shell);
	if (!cmds)
		return (0);
	i = 1;
	while (cmds)
	{
		if (*cmds->operator_type != NONE && cmds->next)
		{
			i = 0;
			break;
		}
		if (ft_strncmp(cmds->command, "history", 7) == 0)
			display_history();
		else if (ft_strncmp(cmds->command, "exit", 4) == 0)
		{
			shell->run = false;
			break ;
		}
		else if (ft_strncmp(cmds->command, "echo", 4) == 0)
			ft_echo(cmds);
		else if (ft_strncmp(cmds->command, "pwd", 3) == 0)
			pwd();
		else if (ft_strncmp(cmds->command, "clear", 5) == 0)
			ft_clear();
		else
		{
			if (!run_env_command(shell, cmds))
			{
				print_invalid_cmd(cmds->command);
				i = 0;
				break ;
			}
		}
		cmds = cmds->next;
		// link command after operator
	}
	// free_cmds(cmds);
	return(i);
}
