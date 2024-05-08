/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage_collector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:58:59 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/08 17:19:31 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	garbage_free(void **garbage)
{
	int	i;

	i = 0;
	while (garbage[i])
		free(garbage[i++]);
	free(garbage);
}

void	ft_garbage_collector(void *ptr, int action)
{
	static void	**garbage = NULL;
	static int	i = 0;

	if (action == GARBAGE_CREATE)
	{
		garbage = malloc(sizeof(void *) * GARBAGE_COLLECTOR_SIZE);
		if (!garbage)
			return (NULL);
	}
	else if (action == GARBAGE_ADD)
	{
		if (i >= GARBAGE_COLLECTOR_SIZE)
		{
			garbage = ft_realloc(garbage, sizeof(void *)
					* GARBAGE_COLLECTOR_SIZE * 2);
			if (!garbage)
				return (NULL);
		}
		garbage[i++] = ptr;
	}
	else if (action == GARBAGE_FREE)
		garbage_free(garbage);
}
