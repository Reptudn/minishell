/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:00:27 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 09:13:03 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// TODO: make heredoc run with any amount of args like: echo << EOF << POG -> this should only escape when EOF and POG are written in order
// FIXME: it segv when the escape sequence is the first thats given in the heredoc
int	run_delimiter(t_shell *shell, t_shunting_node *cmd1, t_shunting_node *cmd2)
{
	char			*heredoc;
	char			*new_heredoc;
	char			*temp;
	int				status;
	char			*nl;
	t_shunting_node	*echo;

	heredoc = malloc(sizeof(char) * 100);
	heredoc[0] = '\0';
	(void)cmd1;
	while (1)
	{
		temp = readline(COLOR_BLACK "heredoc> ");
		if (!temp)
		{
			status = CMD_FAILURE;
			break ;
		}
		if (str_is_equal(temp, cmd2->value))
		{
			status = CMD_SUCCESS;
			free(temp);
			break ;
		}
		new_heredoc = ft_strjoin(heredoc, temp);
		free(heredoc);
		heredoc = ft_strjoin(new_heredoc, "\n");
		free(new_heredoc);
		free(temp);
	}
	if (status == CMD_SUCCESS)
	{
		echo = malloc(sizeof(t_shunting_node));
		echo->value = ft_strdup("echo");
		echo->args = malloc(sizeof(char *) * 2);
		echo->exit_status = malloc(sizeof(int));
		nl = ft_strrchr(heredoc, '\n');
		*nl = '\0';
		echo->args[0] = heredoc;
		echo->args[1] = NULL;
		(void)shell;
		free(echo->value);
		free(echo->args);
		free(echo->exit_status);
		free(echo);
	}
	free(heredoc);
	return (status);
}
