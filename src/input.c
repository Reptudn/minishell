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

void	print_path(void);
int		*is_heredoc(void);

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
		if (node->args)
		{
			while (node->args[++i])
				free(node->args[i]);
		}
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
	if (!line)
		return (NULL);
	return (line);
}

int	command_loop(t_shell *shell)
{
	int				status;
	char			*line;
	t_shunting_yard	*yard;

	line = get_input(prompt_hello());
	status = 0;
	while (*get_run() && line)
	{
		if (ft_strlen(line) == 0)
		{
			free(line);
			line = get_input(prompt_success());
			if (!line)
				break ;
			continue ;
		}
		yard = shunting_yard(ft_split_shell(is_valid_input(line)));
		if (!yard)
		{
			free(line);
			line = get_input(prompt_failure());
			status = CMD_FAILURE;
			continue ;
		}
		status = execute_commands(yard, shell);
		*shell->exit_status = status;
		shunting_yard_destroy(yard);
		free(line);
		line = NULL;
		if (!(*get_run()))
			break ;
		if (status != CMD_SUCCESS)
			line = get_input(prompt_failure());
		else
			line = get_input(prompt_success());
	}
	clear_history();
	if (line)
		free(line);
	return (*shell->exit_status);
}
