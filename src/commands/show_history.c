/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:29:05 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/02 13:06:26 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <readline/history.h>

int	display_history(void)
{
	int			i;
	HIST_ENTRY	*entry;

	i = history_length;
	if (history_length == 1)
	{
		printf("No command history\n");
		return (1);
	}
	while (i >= 0)
	{
		entry = history_get(i);
		if (!entry)
			return (0);
		printf("%-3d:  %s\n", i, entry->line);
		i--;
	}
	return (1);
}
