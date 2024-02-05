/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:56:25 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/05 10:30:32 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../include/minishell.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int is_shell_op(char *str, char *shell_op[], int size)
{
	int i;

	i = 0;
	while (i < size) 
	{
		if (ft_strncmp(str, shell_op[i], ft_strlen(shell_op[i])) == 0)
			return (ft_strlen(shell_op[i]));
		i++;
	}
	return (0);
}
