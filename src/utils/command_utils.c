/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:41:33 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/08 09:02:49 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../include/minishell.h"

int is_operator(char *str)
{
	if (ft_strlen(str) == 1)
	{
		if (str_is_equal(str, "|") == 1)
			return (PIPE);
		if (str_is_equal(str, ">") == 1)
			return (REDIRECT_OUT);	
		if (str_is_equal(str, "<") == 1)
			return (REDIRECT_IN);
	}
	else if (ft_strlen(str) == 2)
	{
		if (str_is_equal(str, "||") == 1)
			return (OR);
		if (str_is_equal(str, "&&") == 1)
			return (AND);
		if (str_is_equal(str, ">>") == 1)
			return (REDIRECT_OUT_APPEND);
		if (str_is_equal(str, "<<") == 1)
			return (REDIRECT_IN_DELIMITER);
	}
	return (NONE);
}

int	str_is_equal(char *str1, char *str2)
{
	int i;

	i = 0;
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	while(str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}