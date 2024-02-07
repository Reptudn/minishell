/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:22:25 by jkauker           #+#    #+#             */
/*   Updated: 2024/02/06 13:34:48 by jkauker          ###   ########.fr       */
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

int	is_valid_input(char **split, char *line)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp_line;

	i = 0;
	if (is_operator(split[0]) != NONE)
		return (0);
	if (get_quote_cout(split[0]) % 2 != 0)
	{
		line = readline("quote> ");
		while (ft_strchr(line, '"') == NULL)
		{
			if (!line)
				return (0);
			tmp = ft_strjoin(line, " ");
			free(line);
			tmp_line = ft_strjoin(tmp, tmp_line);
			free(tmp);
			line = readline("quote> ");
		}
		tmp = line;
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	printf("%s\n", split[i - 1]);
	if (is_operator(ft_strtrim(split[i - 1], " 	")) != NONE)
		return (0);
	return (1);
}
