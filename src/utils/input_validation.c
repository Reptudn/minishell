/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:22:25 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/09 10:54:41 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_quote_cout(char *str)
{
	int	quote_count;
	int	i;

	quote_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			quote_count++;
		i++;
	}
	return (quote_count);
}

char	*handle_missing_quotes(char	*line)
{
	char	*tmp;
	char	*new_line;

	if (ft_strchr(line, '"') != 0 && get_quote_cout(line) % 2 != 0)
	{
		while (get_quote_cout(line) % 2 != 0)
		{
			tmp = readline("\033[0;31mquote> \033[0m");
			if (!tmp)
				return (0);
			new_line = ft_strjoin(line, "\n");
			new_line = ft_strjoin(new_line, tmp);
			free(line);
			if (!new_line)
				return (0);
			line = new_line;
		}
	}
	return (line);
}

char	*is_valid_input(char *line)
{
	int		return_value;
	int		j;

	return_value = 1;
	line = handle_missing_quotes(line);
	if (!line)
		return (0);
	return (line);
}
