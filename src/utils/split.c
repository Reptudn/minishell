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

void	process_string(const char *str, char **result, int *res_i)
{
	char	**shell_op;
	int		i;
	int		start;
	int		op_len;
	int		len;
	char	quote;

	i = 0;
	start = 0;
	shell_op = fill_shell_op();
	while (str[i] != '\0')
	{
		if ((str[i] == '"')
			&& (str[i - 1] && (str[i - 1] == '=')))
			double_quotes(str, i, &start, result, res_i);
		else if ((str[i] == '"')
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
			op_len = is_shell_op((char *) &str[i], shell_op, 10);
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
	i = -1;
	while (shell_op[++i])
		free(shell_op[i]);
	free(shell_op);
}

char	**clean_quotes(char **tmp)
{
	char	**result;
	int		i;
	int		m;

	i = 0;
	while (tmp[i])
		i++;
	result = (char **)malloc((i + 1) * sizeof(char *));
	if (!tmp || !result)
		return (NULL);
	i = -1;
	m = -1;
	while (tmp[++i])
	{
		result[i] = malloc(sizeof(char) * (ft_strlen(tmp[i]) + 1));
		if (!result[i])
			return (NULL);
		if (tmp[i] && !str_is_equal(tmp[i], "(") && !str_is_equal(tmp[i], ")"))
		{
			free(result[++m]);
			result[m] = ft_strdup(tmp[i]);
		}
	}
	result[++m] = NULL;
	return (result);
}

