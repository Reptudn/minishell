/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:14:28 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/28 15:03:19 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	shunting_yard_destroy(t_shunting_yard *yard)
{
	t_shunting_node	*node;
	t_shunting_node	*next_node;
	int				i;

	node = yard->output;
	if (!node)
		return ;
	while (node)
	{
		free(node->value);
		i = -1;
		if (node->args && node->args[0])
			while (node->args[++i])
				free(node->args[i]);
		free(node->args);
		free(node->type);
		free(node->priority);
		free(node->fd);
		free(node->exit_status);
		next_node = node->next;
		free(node);
		node = next_node;
	}
	free(yard);
}

int	command_loop(t_shell *shell)
{
	int				status;
	char			*line;
	t_shunting_yard	*yard;
	char			**split;
	int				i;

	line = readline(PROMPT_HELLO);
	status = 0;
	while (shell->run && line)
	{
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
		yard = shunting_yard(split);
		if (!yard)
		{
			printf("Shunting yard failed\n");
			free(line);
			line = readline(PROMPT_FAILURE);
			status = CMD_FAILURE;
			continue ;
		}
		i = -1;
		while (split[++i])
			free(split[i]);
		free(split);
		printf("%s", COLOR_RESET);
		status = execute_commands(yard, shell, status);
		shunting_yard_destroy(yard);
		free(line);
		line = NULL;
		if (!shell->run)
			break ;
		if (status == CMD_FAILURE || status == CMD_NOT_FOUND || status == 2)
			line = readline(PROMPT_FAILURE);
		else
			line = readline(PROMPT_SUCCESS);
	}
	clear_history();
	if (line)
		free(line);
	return (0);
}
