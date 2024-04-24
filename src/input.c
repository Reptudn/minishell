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
	// int				i;

	node = yard->output;
	if (!node)
		return ;
	while (node)
	{
		free(node->value);
		// i = -1;
		// if (node->args && node->args[0])
		// 	while (node->args[++i]) // CAUSED DOUBLE FREE WHEN I RAN echo *.c but there was no .c file in dir
		// 		free(node->args[i]);
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

char	*get_input(char *prompt)
{
	char	*line;
	char	*tmp;

	if (isatty(fileno(stdin)))
		line = readline(prompt);
	else
	{
		line = get_next_line(fileno(stdin));
		if (!line)
			return (NULL);
		tmp = ft_strtrim(line, "\n");
		if (line)
			free(line);
		line = tmp;
	}
	if (line && ft_strlen(line) > 0)
		add_history(line);
	if (!line)
		return (NULL);
	return (line);
}

int	command_loop(t_shell *shell)
{
	int				status;
	char			*line;
	t_shunting_yard	*yard;
	char			**split;

	line = get_input(prompt_hello());
	status = 0;
	while (*get_run() && line)
	{
		if (ft_strlen(line) == 0)
		{
			free(line);
			line = get_input(prompt_failure());
			if (!line)
				break ;
			continue ;
		}
		line = is_valid_input(line);
		if (!line)
		{
			line = get_input(prompt_failure());
			status = CMD_FAILURE;
			continue ;
		}
		split = ft_split_shell(line);
		if (!split)
		{
			free(line);
			line = get_input(prompt_failure());
			status = CMD_FAILURE;
			continue ;
		}
		yard = shunting_yard(split);
		if (!yard)
		{
			free(line);
			line = get_input(prompt_failure());
			status = CMD_FAILURE;
			continue ;
		}
		free_split(split);
		status = execute_commands(yard, shell);
		shunting_yard_destroy(yard);
		free(line);
		line = NULL;
		if (!*get_run())
			break ;
		if (status == CMD_FAILURE || status == CMD_NOT_FOUND || status == 2)
			line = get_input(prompt_failure());
		else
			line = get_input(prompt_success());
	}
	clear_history();
	if (line)
		free(line);
	return (*shell->exit_status);
}
