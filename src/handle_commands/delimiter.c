/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:00:27 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/21 08:43:11 by jkauker          ###   ########.fr       */
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
	printf("cmd2->value: %s\n", cmd2->value);
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
		free(temp);
		heredoc = ft_strjoin(heredoc, "\n");
	}
	status = CMD_SUCCESS;
	if (status == CMD_SUCCESS)
	{
		t_shunting_node *echo = malloc(sizeof(t_shunting_node));
		echo->value = ft_strdup("echo");
		echo->args = malloc(sizeof(char *) * 2);
		echo->args[0] = heredoc;
		echo->args[1] = NULL;
		status = run_pipe_cmd(echo, cmd1, shell);
		free(echo->value);
		free_split(echo->args);
		free(echo);
	}
	free(heredoc);
	return (status);
}
