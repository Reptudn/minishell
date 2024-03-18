/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:22:25 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/18 10:50:55 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_quote_cout(char *str, char quote)
{
	int	quote_count;
	int	i;

	quote_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == quote)
			quote_count++;
		i++;
	}
	return (quote_count);
}

char	*handle_missing(char *line, char missing)
{
	char	*tmp;
	char	*temp;
	char	*new_line;

	if (ft_strchr(line, missing) != 0 && get_quote_cout(line, missing) % 2 != 0)
	{
		while (get_quote_cout(line, missing) % 2 != 0)
		{
			if (missing == '"')
				tmp = readline("\033[0;31mdquote> \033[0m");
			else
				tmp = readline("\033[0;31msquote> \033[0m");
			if (!tmp)
				return (0);
			new_line = ft_strjoin(line, "\n");
			temp = new_line;
			free(line);
			new_line = ft_strjoin(temp, tmp);
			free(temp);
			if (!new_line)
				return (0);
			line = new_line;
			free(tmp);
		}
	}
	return (line);
}

char	*is_valid_input(char *line)
{
	while (get_quote_cout(line, '"') % 2 != 0
		&& get_quote_cout(line, '"') % 2 != 0)
	{
		line = handle_missing(line, '"');
		if (!line)
			return (0);
		line = handle_missing(line, '\'');
		if (!line)
			return (0);
	}
	return (line);
}
