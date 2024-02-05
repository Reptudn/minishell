/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:14:28 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/05 09:04:59 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>

int	command_loop(t_shell *shell)
{
	char	*line;

	line = (char *)readline(PROMPT);
	while (shell->run)
	{
		if (!line || ft_strlen(line) == 0)
		{
			free(line);
			line = readline(PROMPT);
			continue ;
		}
		printf("%s", COLOR_RESET);
		if (ft_strlen(line) > 0)
			add_history(line);
		if (ft_strncmp(line, "history", 7) == 0)
			display_history();
		else if (ft_strncmp(line, "exit", 4) == 0)
			break ;
		else if (ft_strncmp(line, "echo ", 5) == 0)
			ft_echo(&((t_command){"echo", ft_split(ft_substr(line, 5,
							ft_strlen(line)), ' '), NONE, NULL, NULL}));
		else
			print_invalid_cmd(line);
		free(line);
		line = readline(PROMPT);
	}
	clear_history();
	if (line)
		free(line);
	return (0);
}


