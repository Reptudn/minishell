/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:30:38 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/05 15:16:25 by jkauker          ###   ########.fr       */
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
			break ;
		}
		if (str_is_equal(cmds->command, "history"))
			display_history();
		else if (str_is_equal(cmds->command, "exit"))
		{
			shell->run = false;
			break ;
		}
		else if (str_is_equal(cmds->command, "echo"))
			ft_echo(cmds);
		else if (str_is_equal(cmds->command, "pwd"))
			pwd();
		else if (str_is_equal(cmds->command, "clear"))
			ft_clear();
		else if (str_is_equal(cmds->command, "export"))
			ft_export(shell);
		else if (str_is_equal(cmds->command, "env"))
			ft_env(shell);
		else if (str_is_equal(cmds->command, "unset"))
			ft_unset();
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
