/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_helper_process_string.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:02:47 by nsabia            #+#    #+#             */
/*   Updated: 2024/04/19 08:50:49 by jkauker          ###   ########.fr       */
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

void	single_quotes(const char *str, int i, int *start, char **result, int *res_i)
{
	char	quote;
	int		len;

	quote = str[i];
	*start = i + 1;
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
