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
int		command_loop_helper2(t_shunting_yard *yard, char *line, int status);
int		command_loop_helper(char *line);
int		command_loop_helper3(char *line, t_shunting_yard **yard, int status);

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
	char			*line;
	t_shunting_yard	*yard;
	int				status;

	line = get_input(prompt_hello());
	status = 0;
	while (*get_run() && line)
	{
		if (command_loop_helper3(line, &yard, status))
			continue ;
		// print_all_stacks(yard);
		*shell->exit_status = execute_commands(yard, shell);
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
