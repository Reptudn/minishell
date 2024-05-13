/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:03:12 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/13 13:53:29 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_surrounding_doubleq(char *str, int *changed);

void	insert_str_on_pos_w_len(char **str, char *insert, int pos, int len)
{
	char	*new_str;
	int		i;
	int		k;

	new_str = malloc((ft_strlen(*str) + ft_strlen(insert) - len + 1)
			* sizeof(char));
	if (!new_str)
		return ;
	i = -1;
	k = 0;
	while ((*str)[++i])
	{
		if (i == pos)
			while (*insert)
				new_str[k++] = *insert++;
		if (i < pos || i >= pos + len)
			new_str[k++] = (*str)[i];
	}
	new_str[k] = '\0';
	free(*str);
	*str = new_str;
}

char	*append_single_char(char *str, char c)
{
	int		len;
	char	*out;

	if (!str)
	{
		out = malloc(2 * sizeof(char));
		if (!out)
			return (NULL);
		out[0] = c;
		out[1] = '\0';
	}
	else
	{
		len = ft_strlen(str);
		out = ft_realloc(str, (len + 2) * sizeof(char));
		if (!out)
			return (NULL);
		out[len] = c;
		out[len + 1] = '\0';
	}
	return (out);
}

int	expand_var(char **var_str, char *str)
{
	char		*var;
	int			len;
	t_env_var	*env_var;

	if (*str != '$')
		return (0);
	str++;
	len = 0;
	while (str[len] && ft_isalnum(str[len]))
		len++;
	if (*str == '?' && len == 0)
	{
		var = ft_itoa(*get_shell()->exit_status);
		if (!var)
			return (-1);
		*var_str = ft_strjoin(*var_str, var);
		free(var);
		if (!var_str)
			return (-1);
		return (1);
	}
	var = ft_substr(str, 0, len);
	if (!var)
		return (-1);
	env_var = env_get_by_name(get_shell()->env_vars, var);
	if (!env_var)
	{
		free(var);
		return (len + 1);
	}
	*var_str = ft_strjoin(*var_str, env_var->value);
	free(var);
	if (!var_str)
		return (-1);
	if (len == 0)
		return (1);
	return (len + 1);
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

char	*get_var_str(char *str)
{
	t_temps	temp;
	char	*var_str;

	temp.int_i = -1;
	if (!str)
		return (NULL);
	var_str = NULL;
	while (str && str[++temp.int_i])
	{
		if (str[temp.int_i] == '\'')
		{
			temp.int_i++;
			while (str[temp.int_i] && str[temp.int_i] != '\'')
				var_str = append_single_char(var_str, str[temp.int_i++]);
			continue ;
		}
		if (str[temp.int_i] == '\"')
		{
			temp.int_i++;
			while (str[temp.int_i] && str[temp.int_i] != '\"')
			{
				if (str[temp.int_i] == '$' && str[temp.int_i + 1] != '\"')
					temp.int_i += expand_var(&var_str, str + temp.int_i);
				else
					var_str = append_single_char(var_str, str[temp.int_i++]);
			}
			continue ;
		}
		if (str[temp.int_i] == '$' && str[temp.int_i + 1])
			temp.int_i += expand_var(&var_str, str + temp.int_i) - 1;
		else
			var_str = append_single_char(var_str, str[temp.int_i]);
	}
	if (str)
		free(str);
	return (var_str);
}
