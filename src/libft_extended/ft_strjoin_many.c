/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_many.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:24:10 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/16 08:02:57 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strjoin_many_helper(va_list args)
{
	va_end(args);
	return (1);
}

char	*ft_strjoin_many(int count, ...)
{
	va_list			args;
	t_strjoin_many	strjoin;

	va_start(args, count);
	strjoin.str = ft_strdup("");
	if (!strjoin.str)
		va_end(args);
	if (!strjoin.str)
		return (NULL);
	strjoin.i = 0;
	while (count--)
	{
		strjoin.temp = va_arg(args, char *);
		if (strjoin.temp)
		{
			strjoin.temp_str = ft_strjoin(strjoin.str, strjoin.temp);
			ft_free((strjoin.str));
			if (!strjoin.temp_str && ft_strjoin_many_helper(args))
				return (NULL);
			strjoin.str = strjoin.temp_str;
			strjoin.i++;
		}
	}
	va_end(args);
	return (strjoin.str);
}
