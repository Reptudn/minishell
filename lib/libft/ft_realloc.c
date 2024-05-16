/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:58:59 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/16 10:38:01 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_realloc(void *ptr, size_t size) // TODO: check this function cuz with the normal realloc it works
{
	void	*new_ptr;
	size_t	original_size;

	new_ptr = malloc(size); // malloc or ft_malloc?
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		original_size = ft_strlen((char *) ptr);
		ft_memcpy(new_ptr, ptr, original_size);
		free(ptr); // free or ft_free?
	}
	return (new_ptr);
}
