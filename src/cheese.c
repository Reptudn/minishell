/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheese.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:37:05 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/22 16:10:57 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell	*get_shell(void)
{
	static t_shell	shell;

	return (&shell);
}

int	*get_run(void)
{
	static int	run = 1;

	return (&run);
}
