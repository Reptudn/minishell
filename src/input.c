/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:14:28 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/02 12:14:34 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	command_loop(void)
{
	char	*line;
	// char	**args;

	printf("%s%s%s", COLOR_CYAN, PROMPT, COLOR_YELLOW);

	line = (char *)readline(STDIN_FILENO);
	// args = 0;
	return (0);
	while (line)
	{
		// args = ft_split(line, ' ');
		free(line);
		printf("%s%s%s", COLOR_CYAN, PROMPT, COLOR_YELLOW);
		line = readline(STDIN_FILENO);
	}
	if (line)
		free(line);
	return (0);
}


