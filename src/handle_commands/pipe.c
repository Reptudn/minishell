/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:20:58 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/08 07:46:51 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//TODO: Implement pipe handling like bash that means open as much pipes as there are 

char	*run_pipe(t_shell *shell, t_shunting_node **chain, int counter, int pipe_amount, char *str)
{
	
	return ("your_mum");
}

/*


	echo hello         dup2(pipefd[0], STDIN_FILENO);  close(pipefd[0]); close(pipefd[1]);


	wc -l              dup2(pipefd[1], 1); close(pipefd[0]); close(pipefd[1]);






*/