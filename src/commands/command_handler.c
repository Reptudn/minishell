/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:30:38 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/16 15:23:37 by jkauker          ###   ########.fr       */
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
		// if (*cmds->operator_type == PIPE)
		// {
		// 	if (cmds->next == NULL)
		// 	{
		// 		printf("expected command after pipe\n");
		// 		break ;
		// 	}
		// 	if (run_pipe_cmd(cmds, cmds->next, shell) != 0)
		// 		break ;
		// 	cmds = cmds->next->next;
		// 	continue ;
		// }
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
		// if (*cmds->operator_type == NONE)
		// 	break ;
		// if (*cmds->operator_type == AND)
		// 	cmds = cmds->next;
		// else if (*cmds->operator_type == OR && exit_status != 0)
		// 	cmds = cmds->next;
		break ;
		// link command after operator
	}
	// free_cmds(cmds);
	return(i);
}
