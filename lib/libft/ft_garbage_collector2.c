/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage_collector2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsabia <nsabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:10:59 by nsabia            #+#    #+#             */
/*   Updated: 2024/05/17 12:15:21 by nsabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	*garbage_col_count(void)
{
	static int	count = 0;

	return (&count);
}

int	*garbage_col_size(void)
{
	static int	count = GARBAGE_COL_SIZE;

	return (&count);
}

void	***garbage_col_get(void)
{
	static void	**garbage = NULL;

	return (&garbage);
}

int	ft_garbage_col_create(void)
{
	void	***garbage;

	garbage = garbage_col_get();
	if (*garbage)
		return (1);
	*garbage_col_count() = 0;
	*garbage = malloc(sizeof(void *) * GARBAGE_COL_SIZE);
	if (!*(garbage))
		return (0);
	return (1);
}
