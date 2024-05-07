/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_many.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:24:10 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/07 08:33:21 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strjoin_many(int count, ...)
{
	va_list	args;
	char	*str;
	char	*temp_str;
	char	*temp;
	int		i;

	va_start(args, count);
	str = ft_strdup("");
	if (!str)
	{
		va_end(args);
		return (NULL);
	}
	i = 0;
	while (count--)
	{
		temp = va_arg(args, char *);
		if (temp)
		{
			temp_str = ft_strjoin(str, temp);
			free(str);
			if (!temp_str)
			{
				va_end(args);
				return (NULL);
			}
			str = temp_str;
			i++;
		}
	}
	va_end(args);
	return (str);
}

