/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:14:28 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/08 13:11:51 by jkauker          ###   ########.fr       */
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
		free(node->exit_status);
		next_node = node->next;
		free(node);
		node = next_node;
	}
	free(yard);
}

int	command_loop(t_shell *shell)
{
	char			*line;
	t_shunting_yard	*yard;
	char			**split;
	int				status;

	line = readline(prompt_hello());
	status = 0;
	while (shell->run && line)
	{
		if (ft_strlen(line) == 0)
		{
			free(line);
			line = readline(prompt_success());
			if (!line)
				break ;
			continue ;
		}
		if (ft_strlen(line) > 0)
			add_history(line);
		line = is_valid_input(line);
		if (!line)
		{
			line = readline(prompt_failure());
			status = CMD_FAILURE;
			continue ;
		}
		split = ft_split_shell(line);
		if (!split)
		{
			free(line);
			line = readline(prompt_failure());
			status = CMD_FAILURE;
			continue ;
		}
		yard = shunting_yard(split);
		if (!yard)
		{
			free(line);
			line = readline(prompt_failure());
			status = CMD_FAILURE;
			continue ;
		}
		free_split(split);
		status = execute_commands(yard, shell);
		shunting_yard_destroy(yard);
		free(line);
		line = NULL;
		if (!shell->run)
			break ;
		if (*shell->exit_status != CMD_SUCCESS || status != CMD_SUCCESS)
			line = readline(prompt_failure());
		else
			line = readline(prompt_success());
	}
	clear_history();
	if (line)
		free(line);
	return (*shell->exit_status);
}
