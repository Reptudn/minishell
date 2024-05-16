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

void	process_string_helper(const char *str, t_process_string *string)
{
	string->temp.int_j = 0;
	string->quote = str[string->i];
	while (str[string->i])
	{
		if (str[string->i] == string->quote && string->temp.int_j++ > 0)
		{
			string->temp.charp_i = append_single_char(
					string->temp.charp_i, str[string->i]);
			break ;
		}
		string->temp.charp_i = append_single_char(string->temp.charp_i,
				str[string->i]);
		if (!string->temp.charp_i)
			return ;
		string->i++;
	}
}

int	process_string_helper3(const char *str, t_process_string *string,
		char **result, int *res_i)
{
	if (ft_isspace(str[string->i]))
	{
		if (!str_is_equal(string->temp.charp_i, "")
			|| !str_is_equal(string->temp.charp_i, " "))
			result[(*res_i)++] = string->temp.charp_i;
		string->temp.charp_i = ft_strdup("");
		if (!string->temp.charp_i)
			return (0);
		return (1);
	}
	string->temp.charp_i = append_single_char(string->temp.charp_i,
			str[string->i]);
	if (!string->temp.charp_i)
		return (0);
}

int	process_string_helper2(const char *str, t_process_string *string,
		char **result, int *res_i)
{
	string->temp.int_j = is_shell_op((char *) &str[string->i], string->shell_op, 10);
	if (string->temp.int_j != 0)
	{
		if (!str_is_equal(string->temp.charp_i, "")
			|| !str_is_equal(string->temp.charp_i, " "))
			result[(*res_i)++] = string->temp.charp_i;
		result[(*res_i)++] = ft_substr(&str[string->i], 0,
				string->temp.int_j);
		string->i += string->temp.int_j - 1;
		string->temp.charp_i = ft_strdup("");
		if (!string->temp.charp_i)
			return (0);
	}
	else
		return (process_string_helper3(str, string, result, res_i));
	return (1);
}

int	weird_shell_op(const char *str)
{
	char	**shell_op;
	char	*first_two_chars;
	int		i;

	shell_op = fill_shell_op();
	first_two_chars = malloc(3);
	i = -1;
	first_two_chars[0] = str[0];
	first_two_chars[1] = str[1];
	first_two_chars[2] = '\0';
	while (shell_op[++i])
	{
		if (str[0] == *shell_op[i] || first_two_chars == shell_op[i])
			return (1);
	}
	return (0);
}

void	process_string(const char *str, char **result, int *res_i)
{
	t_process_string	string;

	string.i = -1;
	string.shell_op = fill_shell_op();
	string.temp.charp_i = NULL;
	if (weird_shell_op(str))
		(*res_i)--;
	while (str[++(string.i)])
	{
		if (str[string.i] == '"' || str[string.i] == '\'')
			process_string_helper(str, &string);
		else
		{
			if (!process_string_helper2(str, &string, result, res_i))
				break ;
		}
	}
	if (!str_is_equal(string.temp.charp_i, "")
		|| !str_is_equal(string.temp.charp_i, " "))
		result[(*res_i)++] = string.temp.charp_i;
	result[(*res_i)] = NULL;
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
