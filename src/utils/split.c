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

char		*append_single_char(char *str, char c);

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
	t_temps	temp;
	char	**shell_op;
	int		i;
	char	quote;

	i = -1;
	shell_op = fill_shell_op();
	temp.charp_i = ft_strdup("");
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			temp.int_j = 0;
			quote = str[i];
			while (str[i])
			{
				if (str[i] == quote && temp.int_j++ > 0)
				{
					temp.charp_i = append_single_char(temp.charp_i, str[i]);
					break ;
				}
				temp.charp_i = append_single_char(temp.charp_i, str[i]);
				if (!temp.charp_i)
					return ;
				i++;
			}
		}
		else
		{
			temp.int_j = is_shell_op((char *) &str[i], shell_op, 10);
			if (temp.int_j != 0)
			{
				if (!str_is_equal(temp.charp_i, "")
					|| !str_is_equal(temp.charp_i, " "))
					result[(*res_i)++] = temp.charp_i;
				result[(*res_i)++] = ft_substr(&str[i], 0, temp.int_j);
				i += temp.int_j - 1;
				temp.charp_i = ft_strdup("");
				if (!temp.charp_i)
					return ;
			}
			else
			{
				if (str[i] == ' ')
				{
					if (!str_is_equal(temp.charp_i, "")
						|| !str_is_equal(temp.charp_i, " "))
						result[(*res_i)++] = temp.charp_i;
					temp.charp_i = ft_strdup("");
					if (!temp.charp_i)
						return ;
					continue ;
				}
				temp.charp_i = append_single_char(temp.charp_i, str[i]);
				if (!temp.charp_i)
					return ;
			}
		}
	}
	if (!str_is_equal(temp.charp_i, "")|| !str_is_equal(temp.charp_i, " "))
		result[(*res_i)++] = temp.charp_i;
	result[(*res_i)] = NULL;
	free_split(shell_op);
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
