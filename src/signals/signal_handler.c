/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:57:43 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/05 10:57:33 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGTERM)
	{
		//free(everything on exit)
		exit(0);
	}
	if (signum == SIGINT)
	{
		printf("\n");
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
