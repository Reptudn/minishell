/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_many.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:24:10 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/12 17:13:17 by jkauker          ###   ########.fr       */
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
		va_end(args);
	if (!str)
		return (NULL);
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

/*need to check if the following is also ok:
#include <stdarg.h>
#include <stdlib.h>

char	*ft_strjoin_many(int count, ...);
char	*ft_strjoin_loop(char *str, va_list args);

char	*ft_strjoin_many(int count, ...)
{
	va_list	args;
	char	*str;

	va_start(args, count);
	str = ft_strdup("");
	if (!str)
		return (NULL);
	str = ft_strjoin_loop(str, args);
	va_end(args);
	return (str);
}

char	*ft_strjoin_loop(char *str, va_list args)
{
	char	*temp_str;
	char	*temp;
	int		i;

	i = 0;
	while (count--)
	{
		temp = va_arg(args, char *);
		if (temp)
		{
			temp_str = ft_strjoin(str, temp);
			free(str);
			if (!temp_str)
				return (NULL);
			str = temp_str;
			i++;
		}
	}
	return (str);
}

*/
