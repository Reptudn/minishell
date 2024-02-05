/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:14:28 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/02 12:01:45 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	command_loop(t_shell *shell)
{
	char	*line;

	printf("COMMAND LOOP\n");
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
						ft_strlen(line)), ' '), NONE, NULL, NULL, NULL}));
		else if (ft_strncmp(line, "pwd", 3) == 0)
			pwd();
		else if (ft_strncmp(line, "clear", 5) == 0)
			ft_clear();
		else
		{
			if (!run_env_command(shell, line))
				print_invalid_cmd(line);
		}
		free(line);
		line = readline(PROMPT);
	}
	clear_history();
	if (line)
		free(line);
	return (0);
}


