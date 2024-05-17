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
int		command_loop_helper3(char *line, t_shunting_yard **yard, int *status);

void	shunting_yard_destroy(t_shunting_yard *yard)
{
	(void)yard;
	return ;
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
		ft_free(line);
		line = tmp;
	}
	if (!line)
		return (NULL);
	tmp = ft_strtrim(line, " \t");
	if (isatty(fileno(stdin)))
		free(line);
	else
		ft_free(line);
	if (*tmp == '\0')
		return (ft_strdup(get_input(prompt)));
	return (tmp);
}

int	command_loop(t_shell *shell)
{
	char				*line;
	t_shunting_yard		*yard;
	int					status;

	line = get_input(prompt_hello());
	status = 0;
	while (*get_run() && line)
	{
		if (command_loop_helper3(line, &yard, &status))
			continue ;
		execute_commands(yard, shell);
		shunting_yard_destroy(yard);
		ft_free(line);
		if (!(*get_run()))
			break ;
		if (*shell->exit_status != CMD_SUCCESS)
			line = get_input(prompt_failure());
		else
			line = get_input(prompt_success());
	}
	clear_history();
	return (*shell->exit_status);
}
