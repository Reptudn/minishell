/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:14:28 by jkauker           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/11 10:21:43 by jkauker          ###   ########.fr       */
=======
/*   Updated: 2024/03/11 10:21:17 by jkauker          ###   ########.fr       */
>>>>>>> 0561abd691d02b948ef172efeee9764ad311dacd
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	command_loop(t_shell *shell)
{
<<<<<<< HEAD
	int				status;
	char			*line;
	t_shunting_yard	*yard;
	char			**split;
	char			**split_2;

	line = readline(PROMPT_HELLO);
	// line = readline(PROMPT); //hier liegt das Problem teste es mit NULL du wirst sehen fast keine leaks mehr
=======
	char			*line;
	t_command		*commands;
	t_shunting_node	*shunting;
	int				i;

	line = readline(PROMPT);
>>>>>>> 0561abd691d02b948ef172efeee9764ad311dacd
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
<<<<<<< HEAD
		line = is_valid_input(line);
		if (!line)
=======
		commands = make_cmds(line, shell, i);
		if (!commands)
>>>>>>> 0561abd691d02b948ef172efeee9764ad311dacd
		{
			free(line);
			line = readline(PROMPT_FAILURE);
			continue ;
		}
		split = ft_split_shell(line);
		if (!split)
		{
			free(line);
			line = readline(PROMPT_FAILURE);
			continue ;
		}
		split_2 = filter_variables(split, shell);
		if (!split_2)
		{
			free_split(split);
			free(line);
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
			continue ;
		}
		if (execute_commands(yard, shell) == CMD_FAILURE)
			status = CMD_FAILURE;
		else
			status = CMD_SUCCESS;
		// free the shunting yard
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
