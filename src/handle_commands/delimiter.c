/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:00:27 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/21 09:04:23 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// heredoc
int	run_delimiter(t_shell *shell, t_shunting_node *cmd1, t_shunting_node *cmd2)
{
	char	*heredoc;
	char	*temp;
	int		status;

	heredoc = malloc(sizeof(char));
	heredoc[0] = '\0';
	while (1)
	{
		temp = readline("heredoc> ");
		if (!temp)
		{
			status = CMD_FAILURE;
			break ;
		}
		if (str_is_equal(temp, cmd2->value))
		{
			status = CMD_SUCCESS;
			break ;
		}
		heredoc = ft_strjoin(heredoc, temp);
		heredoc = ft_strjoin(heredoc, "\n");
		free(temp);
	}
	if (status == CMD_SUCCESS)
	{
		t_shunting_node *echo = malloc(sizeof(t_shunting_node));
		echo->value = ft_strdup("echo");
		echo->args = malloc(sizeof(char *) * 2);
		char *nl = ft_strrchr(heredoc, '\n'); //TODO: temp fix
		*nl = '\0';
		echo->args[0] = heredoc;
		echo->args[1] = NULL;
		status = run_pipe_cmd(echo, cmd1, shell);
		free(echo->value);
		free(echo->args[0]);
		free(echo->args[1]);
		free(echo->args);
		free(echo);
	}
	free(heredoc);
	return (status);
}
