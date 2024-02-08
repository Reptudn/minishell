/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:22:25 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/08 10:32:26 by jkauker          ###   ########.fr       */
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

int	handle_missing_quotes(char	*line)
{
	char	*tmp;
	char	*tmp_line;

	if (ft_strchr(line, '"') != 0 && get_quote_cout(line) % 2 != 0)
	{
		line = readline("\033[0;31mquote> \033[0m");
		while (ft_strchr(line, '"') == NULL)
		{
			if (!line)
				return (0);
			tmp = ft_strjoin(line, " ");
			free(line);
			tmp_line = ft_strjoin(tmp, tmp_line);
			free(tmp);
			line = readline("\033[0;31mquote> \033[0m");
		}
		tmp = line;
		return (0);
	}
	return (1);
}

int	is_valid_input(char **split, char *line)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp_line;

	i = 0;
	if (is_operator(split[0]) != NONE)
		return (0);
	handle_missing_quotes(line);
	printf("%s\n", split[i - 1]);
	if (is_operator(split[i - 1]) != NONE)
		return (0);
	return (1);
}
