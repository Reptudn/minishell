/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:14:28 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/05 14:06:52 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	command_loop(t_shell *shell)
{
	char	*line;

	line = (char *)readline(PROMPT);
	while (shell->run)
	{
		if (!line)
			break;
		if (ft_strlen(line) == 0)
		{
			free(line);
			line = readline(PROMPT);
			continue ;
		}
		printf("%s", COLOR_RESET);
		if (ft_strlen(line) > 0)
			add_history(line);
		command_handler(shell, line);
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


