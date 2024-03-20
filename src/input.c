/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:14:28 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/20 10:29:11 by jkauker          ###   ########.fr       */
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
	// while (node)
	// {
	// 	free(node->value);
	// 	i = -1;
	// 	// if (node->args && node->args[0])
	// 	// 	while (node->args[++i])
	// 	// 		free(node->args[i]);
	// 	free(node->args);
	// 	free(node->type);
	// 	free(node->priority);
	// 	free(node->fd);
	// 	free(node->exit_status);
	// 	next_node = node->next;
	// 	free(node);
	// 	node = next_node;
	// }
	free(yard);
}

int	command_loop(t_shell *shell)
{
	int				status;
	char			*line;
	t_shunting_yard	*yard;
	char			**split;
	char			**split_2;

	line = readline(PROMPT_HELLO);
	if (!line)
		return (0);
	status = 0;
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
			printf("Shunting yard failed\n");
			free_split(split_2);
			free(line);
			line = readline(PROMPT_FAILURE);
			status = CMD_FAILURE;
			continue ;
		}
		printf("%s", COLOR_RESET);
		status = execute_commands(yard, shell, status);
		shunting_yard_destroy(yard);
		free_split(split_2);
		free(line);
		line = NULL;
		if (!shell->run)
			break ;
		if (status == CMD_FAILURE || status == CMD_NOT_FOUND || status == 2)
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
