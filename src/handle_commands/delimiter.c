/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:48:04 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/11 09:30:18 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_cmd_chain(t_shunting_node **chain);

// TODO: make heredoc run with any amount of args like: echo << EOF << POG -> this should only escape when EOF and POG are written in order
// FIXME: it segv when the escape sequence is the first thats given in the heredoc
//TODO: listen to "fuck me gently", not a banger but still culture or so the people say
int	run_delimiter(t_shell *shell, t_shunting_node **chain)
{
	char			*heredoc;
	char			*new_heredoc;
	char			*temp;
	int				status;
	char			*nl;
	t_shunting_node	*echo;
	int				counter;

	heredoc = malloc(sizeof(char) * 100);
	heredoc[0] = '\0';
	counter = 1;
	// print_cmd_chain(chain);
	while (1)
	{
		temp = readline("heredoc> ");
		if (!temp)
		{
			status = CMD_FAILURE;
			break ;
		}
		if (chain[counter] && str_is_equal(temp, (chain[counter])->value))
			counter++;
		if (chain[counter] == NULL)
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