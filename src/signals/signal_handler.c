/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:57:43 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 14:27:10 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// TODO: i think we peint one nl too much when pressing control + c
void	signal_handler(int signum)
{
	if (signum == SIGTERM)
	{
		g_run = 0;
		return ;
	}
	if (signum == SIGINT)
		printf("\n");
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// TODO: implement all those

// XXX: This function is being called when goign to a child process
void	signal_ignore_parent(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

// XXX: This function is being called when going back to the parent process
void	signal_restore_parent(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
