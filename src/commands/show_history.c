/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:29:05 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/02 10:32:39 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <readline/history.h>

// TODO: do we really need this?
int	display_history(void)
{
	int			i;
	HIST_ENTRY	*entry;

	i = 0;
	if (history_length == 1)
	{
		printf("No command history\n");
		return (CMD_SUCCESS);
	}
	while (i < history_length)
	{
		entry = history_get(i + 1);
		if (!entry)
			return (CMD_FAILURE);
		printf("%-3d↠  %s\n", i + 1, entry->line);
		i++;
	}
	return (CMD_SUCCESS);
}
