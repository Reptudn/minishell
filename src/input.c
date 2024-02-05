/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:14:28 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/05 08:51:49 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>

int	command_loop(t_shell *shell)
{
	char	*line;

	// printf("%s%s%s", COLOR_CYAN, PROMPT, COLOR_YELLOW);
	line = (char *)readline(PROMPT); //STDIN_FILENO
	while (line && shell->run)
	{
		printf("%s", COLOR_RESET);
		if (ft_strlen(line) > 0)
			add_history(line);
		if (ft_strncmp(line, "history", 7) == 0)
			display_history();
		else if (ft_strncmp(line, "exit", 4) == 0)
			break ;
		else if (ft_strncmp(line, "echo ", 5) == 0)
			ft_echo(&((t_command){"echo", ft_split(ft_substr(line, 5, ft_strlen(line)), ' '), NONE, NULL, NULL}));
		else
			print_invalid_cmd(line);
		free(line);
		// printf("%s%s%s", COLOR_CYAN, PROMPT, COLOR_YELLOW);
		line = readline(PROMPT); //STDIN_FILENO
	}
	clear_history();
	if (line)
		free(line);
	return (0);
}


