/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:05:29 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 10:40:17 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	run_pipe_cmd(t_shunting_node *cmd1, t_shunting_node *cmd2, t_shell *shell)
// {
// 	// int		fd[2];
// 	// pid_t	pid;
// 	// char	*cmd_path;
// 	// char	*cmd_path2;
// 	// char	**envp;

// 	// printf("pipe");
// 	// if (pipe(fd) == -1)
// 	// 	return (0);
// 	// envp = env_to_envp(shell->env_vars);
// 	// pid = fork();
// 	// if (pid < 0)
// 	// 	return (0);
// 	// else if (pid == 0)
// 	// {
// 	// 	dup2(fd[1], 1);
// 	// 	close(fd[0]);
// 	// 	close(fd[1]);
// 	// 	cmd_path = get_env_path_to_cmd(shell, cmd1->value);
// 	// 	if (!cmd_path)
// 	// 		return (0);
// 	// 	if (execve(cmd_path, make_env_args(cmd1->value, cmd1->args), envp) == -1)
// 	// 		return (0);
// 	// }
// 	// else
// 	// {
// 	// 	waitpid(pid, NULL, 0);
// 	// 	dup2(fd[0], 0);
// 	// 	close(fd[0]);
// 	// 	close(fd[1]);
// 	// 	cmd_path2 = get_env_path_to_cmd(shell, cmd2->value);
// 	// 	if (!cmd_path2)
// 	// 		return (0);
// 	// 	if (execve(cmd_path2, make_env_args(cmd2->value, cmd2->args), envp) == -1)
// 	// 		return (0);
// 	// }
// 	return (1);
// }
