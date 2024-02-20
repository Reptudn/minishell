/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:14:28 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/20 12:07:55 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	command_loop(t_shell *shell)
{
	char		*line;
	t_command	*commands;

	line = (char *)readline(PROMPT);
	if (!line)
		return (0);
	while (shell->run)
	{
		if (!line)
			break ;
		if (ft_strlen(line) == 0)
		{
			free(line);
			line = readline(PROMPT);
			continue ;
		}
		printf("%s", COLOR_RESET);
		if (ft_strlen(line) > 0)
			add_history(line);
		commands = make_cmds(line, shell);
		if (!commands)
		{
			printf("cmd failed\n");
			return (0);
		}
		else
		{
			while (commands->prev)
				commands = commands->prev;
			execute_commands(shell, commands, commands->next);
		}
		free(line);
		if (!shell->run)
			break ;
		line = readline(PROMPT);
	}
	clear_history();
	// if (line)
	// 	free(line);
	return (0);
}


