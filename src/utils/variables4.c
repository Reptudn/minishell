/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsabia <nsabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:49:41 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/17 12:24:25 by nsabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*append_single_char(char *str, char c);
int		handle_space(char **var_str);

static int	handle_question_mark(char **var_str, char *str)
{
	char	*var;
	char	*tmp;

	(void)str;
	var = ft_itoa(*get_shell()->exit_status);
	if (!var)
		return (-1);
	tmp = ft_strjoin(*var_str, var);
	*var_str = tmp;
	if (!var_str)
		return (-1);
	return (2);
}

static char	*handle_trim_helper(char **split, int *i, char *tmp, char **var_str)
{
	char	*trimmed;

	while (split[++(*i)])
	{
		if ((*i) == 0)
		{
			tmp = ft_strjoin(" ", split[(*i)]);
			if (!tmp)
				return (NULL);
			split[(*i)] = tmp;
		}
		trimmed = ft_strjoin(*var_str, split[(*i)]);
		if (!trimmed)
			return (NULL);
		*var_str = trimmed;
		trimmed = ft_strjoin(*var_str, " ");
		if (!trimmed)
			return (NULL);
		*var_str = trimmed;
	}
	return (trimmed);
}

static char	*handle_trim(t_env_var *env_var, char **var_str)
{
	char	*trimmed;
	char	**split;
	int		i;
	char	*tmp;

	tmp = NULL;
	split = ft_split(env_var->value, ' ');
	if (!split)
		return (NULL);
	i = -1;
	trimmed = handle_trim_helper(split, &i, tmp, var_str);
	if (trimmed && str_is_equal(trimmed, " "))
		return (NULL);
	return (trimmed);
}

static int	handle_var(char **var_str, char *str, int len, bool trim)
{
	char		*var;
	t_env_var	*env_var;
	char		*temp_var_str;

	var = ft_substr(str, 0, len);
	if (!var)
		return (-1);
	env_var = env_get_by_name(get_shell()->env_vars, var);
	if (!env_var)
		return (len + 1);
	if (trim && str + len && ft_strchr(env_var->value, ' '))
		*var_str = handle_trim(env_var, var_str);
	else
	{
		temp_var_str = ft_strjoin(*var_str, env_var->value);
		(*var_str) = ft_strdup(temp_var_str);
	}
	if (!var_str)
		return (-1);
	if (len == 0)
		return (1);
	return (len + 1);
}

int	expand_var(char **var_str, char *str, bool trim)
{
	int	len;

	if (*str != '$')
		return (0);
	str++;
	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	if (*str == '?' && len == 0)
		return (handle_question_mark(var_str, str));
	else if (*str == ' ' || *str == '\n')
		return (handle_space(var_str));
	else
		return (handle_var(var_str, str, len, trim));
}
