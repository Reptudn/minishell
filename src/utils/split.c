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

char	*create_split_string(const char *str, int start, int len)
{
	char	*result;

	result = (char *)malloc((len + 1) * sizeof(char));
	ft_strncpy(result, &str[start], len);
	result[len] = '\0';
	return (result);
}

char	*create_operator_string(const char *str, int len)
{
	char	*result;

	result = malloc((len + 1) * sizeof(char));
	ft_strncpy(result, &str[0], len);
	result[len] = '\0';
	return (result);
}

void	update_indices(int *i, int *start, int len, int op_len)
{
	if (op_len > 0)
	{
		*i += op_len;
		*start = *i;
	}
	else if (len > 0)
	{
		(*i)++;
		*start = *i;
	}
	else
		(*i)++;
}

// FIXME: This functin doesnt check if quotes are in the middle of the string aka inside other quotes and nt remove them
// TODO: ignore open and close brackets
void	process_string(const char *str, char **result, int *res_i)
{
	char	*shell_op[] = {"||", "&&", "<<", "<", ">>", ">", " ", "(", ")", "|"};
	int		i;
	int		start;
	int		op_len;
	int		len;
	char	quote;

	i = 0;
	start = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '"' || str[i] == '\'')
			&& (str[i - 1] && (str[i - 1] == '=')))
		{
			quote = str[i];
			while (str[i - 1] && str[i] != ' ')
				i--;
			start = i + 1;
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
				len = i - start;
				if (len > 0)
				{
					result[*res_i] = create_split_string(str, start, len);
					(*res_i)++;
				}
				if (str[i] != '\0')
					i++;
				start = i;
			}
		}
		else if ((str[i] == '"' || str[i] == '\'')
			&& (str[i - 1] && (str[i - 1] == ' ')))
		{
			quote = str[i];
			start = i + 1;
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i + 1] && str[i + 1] != ' ' && str[i + 1] != '\0')
				i++;
			else
			{
				len = i - start;
				if (len > 0)
				{
					result[*res_i] = create_split_string(str, start, len);
					(*res_i)++;
				}
				if (str[i] != '\0')
					i++;
				start = i;
			}
		}
		else
		{
			op_len = is_shell_op((char *) &str[i], shell_op,
					sizeof(shell_op) / sizeof(shell_op[0]));
			if (op_len > 0)
				len = i - start;
			else if (str[i + 1] == '\0')
				len = i - start + 1;
			else
				len = 0;
			if (len > 0)
			{
				result[*res_i] = create_split_string(str, start, len);
				(*res_i)++;
			}
			if (op_len > 0)
			{
				result[*res_i] = create_operator_string(&str[i], op_len);
				(*res_i)++;
			}
			update_indices(&i, &start, len, op_len);
		}
	}
}

char	**clean_quotes(char **temp)
{
	char	**result;
	int		i;
	int		m;

	if (!temp)
		return (NULL);
	i = 0;
	while (temp[i])
		i++;
	result = (char **)malloc((i + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = -1;
	m = -1;
	while (temp[++i])
	{
		result[i] = malloc(sizeof(char) * (ft_strlen(temp[i]) + 1));
		if (!result[i])
			return (NULL);
		if (!str_is_equal(temp[i], "(") && !str_is_equal(temp[i], ")") && temp[i])
			result[++m] = strdup(temp[i]);
	}
	result[++m] = NULL;
	return (result);
}

char	**ft_split_shell(const char *str)
{
	char	**temp;
	int		res_i;
	char	**result;
	int		k;

	res_i = 0;
	k = -1;
	temp = (char **)malloc((strlen(str) + 1) * sizeof(char *));
	process_string(str, temp, &res_i);
	temp[res_i] = NULL;
	result = (char **)malloc((res_i + 1) * sizeof(char *));
	result[res_i] = NULL;
	result = clean_data(temp, result);
	free(temp);
	temp = result;
	result = clean_quotes(temp);
	while (temp[++k])
		free(temp[k]);
	free(temp);
	temp = NULL;
	return (result);
}
