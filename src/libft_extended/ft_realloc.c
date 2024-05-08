/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:58:59 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/08 09:42:40 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	size_t	original_size;

	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		original_size = ft_strlen((char *) ptr);
		ft_memcpy(new_ptr, ptr, original_size);
		free(ptr);
	}
	return (new_ptr);
}

