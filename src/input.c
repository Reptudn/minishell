/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:14:28 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/02 13:32:12 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>

int	command_loop(t_shell *shell)
{
	char	*line;

	printf("%s%s%s", COLOR_CYAN, PROMPT, COLOR_YELLOW);
	line = (char *)readline(STDIN_FILENO);
	while (line && shell->run)
	{
		printf("%s", COLOR_RESET);
		if (ft_strlen(line) > 0)
			add_history(line);
		if (ft_strncmp(line, "history", 7) == 0)
			display_history();
		else if (ft_strncmp(line, "exit", 4) == 0)
			break ;
		else
			printf("%scommand not found: %s%s\n%s", COLOR_RED,
				COLOR_MAGENTA, line, COLOR_RESET);
		free(line);
		printf("%s%s%s", COLOR_CYAN, PROMPT, COLOR_YELLOW);
		line = readline(STDIN_FILENO);
	}
	clear_history();
	if (line)
		free(line);
	return (0);
}


