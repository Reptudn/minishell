/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_chain.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:21:25 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/02 15:15:18 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_shunting_node	*get_operator_with_index(t_shunting_node *nodes, int index);

void			yard_pop(t_shunting_node *node, t_shunting_yard *yard);

int				run_pipe_cmd(t_shunting_node *cmd1, t_shunting_node *cmd2,
					t_shell *shell, int in_fd);
int				redirect_in(t_shunting_node *cmd,
					t_shunting_node *cmd2, t_shell *shell, int fd);
int				redirect_out(t_shunting_node *cmd, t_shunting_node *cmd2,
					int fd);
int				run_append(t_shell *shell, t_shunting_node *cmd1,
					t_shunting_node *cmd2, int fd);
int				run_delimiter(t_shell *shell, t_shunting_node *cmd1,
					t_shunting_node *cmd2, int fd);

void			replace_variable(char **args, t_shell *shell, int status);

int	select_runner(t_shunting_node *operator, t_shell *shell, int fd)
{
	t_shunting_node	*cmd1;
	t_shunting_node	*cmd2;

	if (!operator)
		return (CMD_FAILURE);
	cmd2 = operator->prev;
	if (!cmd2)
		return (CMD_FAILURE);
	cmd1 = cmd2->prev;
	if (!cmd1)
		return (CMD_FAILURE);
	if (*operator->type == PIPE)
		return (run_pipe_cmd(cmd1, cmd2, shell, fd));
	else if (*operator->type == REDIRECT_IN)
		return (redirect_in(cmd1, cmd2, shell, fd));
	else if (*operator->type == REDIRECT_OUT)
		return (redirect_out(cmd1, cmd2, fd));
	else if (*operator->type == REDIRECT_OUT_APPEND)
		return (run_append(shell, cmd1, cmd2, fd));
	else if (*operator->type == REDIRECT_IN_DELIMITER)
		return (run_delimiter(shell, cmd1, cmd2, fd));
	return (CMD_SUCCESS);
}

char	*get_temp_file_content(int fd)
{
	char	*line;
	char	*content;

	content = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		content = ft_strjoin(content, line);
		content = ft_strjoin(content, "\n");
		free(line);
		line = get_next_line(fd);
	}
	get_next_line(-1);
	close(fd);
	printf("Temp file content: %s\n", content);
	return (content);
}

// TODO: Implement pipe_chain function into the handler
int	pipe_chain(t_shunting_yard *yard, t_shunting_node *stack, t_shell *shell)
{
	int				fd;
	t_shunting_node	*operator;
	int				status;
	t_shunting_node	*echo;

	if (!stack)
		return (CMD_FAILURE);
	operator = get_operator_with_index(stack, 0);
	if (!operator)
		return (CMD_SUCCESS);
	fd = open("/tmp/minishell.tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (CMD_FAILURE);
	while (operator && (*operator->type == PIPE
			|| *operator->type >= REDIRECT_IN))
	{
		status = select_runner(operator, shell, fd);
		if (status > CMD_SUCCESS)
			return (status);
		yard_pop(operator->prev->prev, yard);
		echo = operator->prev;
		echo->value = ft_strdup("echo");
		echo->args = ft_split("-n  ", ' ');
		echo->type = NONE;
		yard_pop(operator, yard);
		operator = get_operator_with_index(operator->next, 0);
	}
	echo->args = ft_split(get_temp_file_content(fd), ' ');
	close(fd);
	return (CMD_SUCCESS);
}
