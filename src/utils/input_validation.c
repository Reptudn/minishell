/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:22:25 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/18 11:13:34 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_quote_cout(char *str, char quote)
{
	int		quote_count;
	int		i;

	quote_count = 0;
	i = -1;
	while (str[++i])
		if (str[i] == quote)
			quote_count++;
	return (quote_count);
}

bool	is_valid_quotes(char *line, char *missing)
{
	char	current_quote;
	int		i;

	current_quote = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (current_quote == 0)
				current_quote = line[i];
			else if (current_quote == line[i])
				current_quote = 0;
		}
	}
	if (current_quote != 0)
		*missing = current_quote;
	return (current_quote == 0);
}

char	*read_and_append(char *line, char missing)
{
	char	*tmp;
	char	*temp;
	char	*new_line;

	if (missing == '"')
		tmp = readline(prompt_dquote());
	else
		tmp = readline(prompt_squote());
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
	return (line);
}

char	*handle_missing(char *line, char missing)
{
	if (ft_strchr(line, missing) != 0 && !is_valid_quotes(line, &missing))
	{
		while (!is_valid_quotes(line, &missing))
		{
			line = read_and_append(line, missing);
			if (!line)
				return (0);
		}
	}
	return (line);
}

char	*is_valid_input(char *line)
{
	char	missing;

	missing = 0;
	if (!line)
		return (0);
	while (!is_valid_quotes(line, &missing))
	{
		line = handle_missing(line, missing);
		if (!line)
			return (0);
	}
	return (line);
}
