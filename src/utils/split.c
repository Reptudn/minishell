/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:06:44 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 09:23:13 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../include/minishell.h"

char	*append_single_char(char *str, char c);

void	process_string(const char *str, char **result, int *res_i)
{
	t_process_string	string;

	string.i = -1;
	string.shell_op = fill_shell_op();
	string.temp.charp_i = NULL;
	while (str[++(string.i)])
	{
		if (str[string.i] == '"' || str[string.i] == '\'')
		{
			string.temp.int_j = 0;
			string.quote = str[string.i];
			while (str[string.i])
			{
				if (str[string.i] == string.quote && string.temp.int_j++ > 0)
				{
					string.temp.charp_i = append_single_char(
							string.temp.charp_i, str[string.i]);
					break ;
				}
				string.temp.charp_i = append_single_char(string.temp.charp_i,
						str[string.i]);
				if (!string.temp.charp_i)
					return ;
				string.i++;
			}
		}
		else
		{
			string.temp.int_j = is_shell_op((char *) &str[string.i],
					string.shell_op, 10);
			if (string.temp.int_j != 0)
			{
				if (!str_is_equal(string.temp.charp_i, "")
					|| !str_is_equal(string.temp.charp_i, " "))
					result[(*res_i)++] = string.temp.charp_i;
				result[(*res_i)++] = ft_substr(&str[string.i], 0,
						string.temp.int_j);
				string.i += string.temp.int_j - 1;
				string.temp.charp_i = ft_strdup("");
				if (!string.temp.charp_i)
					return ;
			}
			else
			{
				if (ft_isspace(str[string.i]))
				{
					if (!str_is_equal(string.temp.charp_i, "")
						|| !str_is_equal(string.temp.charp_i, " "))
						result[(*res_i)++] = string.temp.charp_i;
					string.temp.charp_i = ft_strdup("");
					if (!string.temp.charp_i)
						return ;
					continue ;
				}
				string.temp.charp_i = append_single_char(string.temp.charp_i,
						str[string.i]);
				if (!string.temp.charp_i)
					return ;
			}
		}
	}
	if (!str_is_equal(string.temp.charp_i, "") || !str_is_equal(string.temp.charp_i, " "))
		result[(*res_i)++] = string.temp.charp_i;
	result[(*res_i)] = NULL;
	free_split(string.shell_op);
}

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
	{
		if (result)
			free(result);
		return (NULL);
	}
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
