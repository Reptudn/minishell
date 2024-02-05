/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:41:33 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/05 13:22:21 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../include/minishell.h"

int is_operator(char *str)
{
	if (ft_strlen(str) == 1)
	{
		if (ft_strncmp(str, "|", 1) == 0)
			return (PIPE);
		if (ft_strncmp(str, ">", 1) == 0)
			return (REDIRECT_OUT);	
		if (ft_strncmp(str, "<", 1) == 0)
			return (REDIRECT_IN);
	}
	else if (ft_strlen(str) == 2)
	{
		if (ft_strncmp(str, "||", 1) == 0)
			return (OR);
		if (ft_strncmp(str, "&&", 1) == 0)
			return (AND);
		if (ft_strncmp(str, ">>", 1) == 0)
			return (REDIRECT_OUT_APPEND);
		if (ft_strncmp(str, "<<", 1) == 0)
			return (REDIRECT_IN_DELIMITER);
	}
	return (NONE);
}

