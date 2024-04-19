/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_helper_process_string.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsabia <nsabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:02:47 by nsabia            #+#    #+#             */
/*   Updated: 2024/04/18 15:29:46 by nsabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	double_quotes(const char *str, int i, int *start, char **result, int *res_i)
{
	char	quote;
	int		len;

	quote = str[i];
	while (str[i - 1] && str[i] != ' ')
		i--;
	*start = i + 1;
	i++;
	while (str[i] && str[i] != quote)
		i++;
	i++;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i + 1] && str[i + 1] != ' ' && str[i + 1] != '\0')
		i++;
	else
	{
		len = i - *start;
		if (len > 0)
		{
			result[*res_i] = create_split_string(str, *start, len);
			(*res_i)++;
		}
		if (str[i] != '\0')
			i++;
		*start = i;
	}
}
