/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:14:28 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/13 15:03:44 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	command_loop(t_shell *shell)
{
	int				status;
	char			*line;
	t_shunting_yard	*yard;
	char			**split;
	char			**split_2;

	line = readline(PROMPT_HELLO);
	// line = readline(PROMPT); //hier liegt das Problem teste es mit NULL du wirst sehen fast keine leaks mehr
	if (!line)
		return (0);
	status = -1;
	while (shell->run)
	{
		if (!line)
			break ;
		if (ft_strlen(line) == 0)
		{
			free(line);
			line = readline(PROMPT_SUCCESS);
			if (!line)
				break ;
			continue ;
		}
		printf("%s", COLOR_RESET);
		if (ft_strlen(line) > 0)
			add_history(line);
		line = is_valid_input(line);
		if (!line)
		{
			free(line);
			line = readline(PROMPT_FAILURE);
			status = CMD_FAILURE;
			continue ;
		}
		split = ft_split_shell(line);
		if (!split)
		{
			free(line);
			line = readline(PROMPT_FAILURE);
			status = CMD_FAILURE;
			continue ;
		}
		split_2 = filter_variables(split, shell);
		if (!split_2)
		{
			free_split(split);
			free(line);
			status = CMD_FAILURE;
			line = readline(PROMPT_FAILURE);
		}
		free_split(split);
		yard = shunting_yard(split_2);
		if (!yard)
		{
			printf("Shtunting yard failed\n");
			free_split(split_2);
			free(line);
			line = readline(PROMPT_FAILURE);
			status = CMD_FAILURE;
			continue ;
		}
		printf("%s", COLOR_YELLOW);
		if (execute_commands(yard, shell) == CMD_FAILURE)
			status = CMD_FAILURE;
		else
			status = CMD_SUCCESS;
		free_split(split_2);
		free(line);
		line = NULL;
		if (!shell->run)
			break ;
		if (status == 1)
			line = readline(PROMPT_FAILURE);
		else
			line = readline(PROMPT_SUCCESS);
		if (!line)
			break ;
	}
	clear_history();
	if (line)
		free(line);
	return (0);
}
