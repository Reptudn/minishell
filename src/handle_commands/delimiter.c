/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:48:04 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/11 14:43:27 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_cmd_chain(t_shunting_node **chain);

// TODO: make heredoc run with any amount of args like: echo << EOF << POG -> this should only escape when EOF and POG are written in order
// FIXME: it segv when the escape sequence is the first thats given in the heredoc
char	*run_delimiter(t_shunting_node **chain)
{
	char			*heredoc;
	char			*new_heredoc;
	char			*temp;
	int				status;
	int				counter;

	heredoc = malloc(sizeof(char) * 100);
	heredoc[0] = '\0';
	counter = 1;
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
	*chain[0]->exit_status = status;
	return (heredoc);
}
// TODO: i think heredoc is not freed in the end