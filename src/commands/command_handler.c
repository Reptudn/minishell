/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:30:38 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/20 10:50:07 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	command_handler(t_shell *shell, char *line)
{
	t_command	*cmds;
	int			exit_status;
	int			i;

	cmds = make_cmds(line, shell);
	if (!cmds)
	{
		printf("cmd failed\n");
		return (0);
	}
	i = 1;
	while (cmds)
	{
		if (str_is_equal(cmds->command, "history"))
			display_history();
		else if (str_is_equal(cmds->command, "exit"))
		{
			shell->run = false;
			break ;
		}
		else if (str_is_equal(cmds->command, "echo"))
			exit_status = ft_echo(cmds);
		else if (str_is_equal(cmds->command, "pwd"))
			exit_status = pwd();
		else if (str_is_equal(cmds->command, "clear"))
			exit_status = ft_clear();
		else if (str_is_equal(cmds->command, "export"))
			exit_status = ft_export(shell);
		else if (str_is_equal(cmds->command, "env"))
			exit_status = ft_env(shell);
		else if (str_is_equal(cmds->command, "unset"))
			exit_status = ft_unset();
		else if (str_is_equal(cmds->command, "cd"))
			exit_status = ft_cd(cmds, shell);
		else if (ft_strchr(cmds->command, '=') != NULL)
		{
			cmds = cmds->next;
			continue ;
		}
		else
		{
			exit_status = run_env_command(shell, cmds);
			if (exit_status <= 0)
			{
				if (exit_status == 0)
					print_invalid_cmd(cmds->command);
				i = 0;
				break ;
			}
		}
		break ;
	}
	free_cmds(cmds);
	return(i);
}
