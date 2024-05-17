/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 06:46:57 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/17 06:47:29 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../include/minishell.h"

char	**clean_quotes(char **tmp)
{
	char	**result;
	int		i;
	int		m;

	i = 0;
	while (tmp[i])
		i++;
	result = (char **)ft_calloc((i + 1), sizeof(char *));
	if (!tmp || !result)
		return (NULL);
	i = -1;
	m = -1;
	while (tmp[++i])
	{
		if (!str_is_equal(tmp[i], "(") && !str_is_equal(tmp[i], ")"))
			result[++m] = ft_strdup(tmp[i]);
	}
	result[++m] = NULL;
	return (result);
}
