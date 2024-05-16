/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:58:59 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/16 12:27:29 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	char	*newptr;

	if (!ptr)
		return (ft_malloc(new_size));
	newptr = ft_malloc(new_size);
	if (!newptr)
		return (ptr);
	memcpy(newptr, ptr, old_size);
	// ft_free(ptr);
	return (newptr);
}
