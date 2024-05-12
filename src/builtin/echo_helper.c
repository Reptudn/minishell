/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 09:48:59 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/12 10:17:58 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_valid_flag(char *str)
{
	if (str[0] != '-')
		return (false);
	str++;
	while (*str == 'n')
		str++;
	return (ft_isspace(*str) || *str == '\0');
}

char	*get_first(char *str)
{
	while (*str)
	{
		if (is_valid_flag(str))
		{
			while (*str != ' ' && *str != '\0')
				str++;
			while (ft_isspace(*str))
				str++;
		}
		else
			return (str);
	}
	return (str);
}

int	args_len(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}
