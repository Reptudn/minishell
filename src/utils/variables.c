/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:05:49 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/08 09:40:01 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_matching_files(char *pattern);
char	*remove_surrounding_singleq(char *str, int *changed);
char	*remove_surrounding_doubleq(char *str, int *changed);

void	handle_env_var(char **arg, t_shell *shell)
{
	char		*var;
	t_env_var	*env_var;

	env_var = env_get_by_name(shell->env_vars, *arg + 1);
	if (!env_var)
		var = ft_strdup("");
	else
		var = ft_strdup(env_var->value);
	if (!var)
		return ;
	free(*arg);
	*arg = var;
}

void	remove_closing_quotes(char **str)
{
	int		i;
	int		j;
	char	quote;
	char	*new_str;

	i = -1;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(*str) + 1));
	while (str && new_str && *str && (*str)[++i])
	{
		if ((*str)[i] != '\"')
		{
			new_str[j++] = (*str)[i];
			continue ;
		}
		quote = (*str)[i];
		while ((*str)[i] && (*str)[i] != quote)
			new_str[j++] = (*str)[i++];
	}
	if (*str)
		free(*str);
	if (new_str)
		new_str[j] = '\0';
	*str = new_str;
}

char	*remove_surrounding_quotes(char *str)
{
	int		changed;

	changed = 0;
	while (str && ((str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
			|| (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"'))
		&& !changed)
	{
		str = remove_surrounding_doubleq(str, NULL);
		if (str_is_equal(str, ""))
			break ;
		str = remove_surrounding_singleq(str, &changed);
	}
	if (!changed)
		remove_closing_quotes(&str);
	return (str);
}

// TODO: when something fails return false
// void	replace_variable(char **value, char ***args)
// {
// 	int		i;
// 	char	*matching;

// 	i = -1;
// 	if (!args || !value || (!*args && **args == NULL))
// 		return ;
// 	if (str_is_equal(*value, "''") || str_is_equal(*value, "\"\""))
// 	{
// 		if (*value)
// 			free(*value);
// 		*value = ft_strdup("");
// 	}
// 	else
// 		*value = get_var_str(*value);
// 	while (*args && (*args)[++i])
// 	{
// 		if (args && *args && (*args)[i] && (str_is_equal((*args)[i], "''")
// 			|| str_is_equal((*args)[i], "\"\"")))
// 		{
// 			free((*args)[i]);
// 			(*args)[i] = ft_strdup("");
// 			continue ;
// 		}
// 		if ((*args)[i] && (ft_strchr((*args)[i], '$')
// 			|| ft_strchr((*args)[i], '"')
// 			|| ft_strchr((*args)[i], '\'')))
// 			(*args)[i] = get_var_str((*args)[i]);
// 		if (!((*args)[i]))
// 			break ;
// 		matching = get_matching_files((*args)[i]);
// 		if (matching)
// 		{
// 			free((*args)[i]);
// 			(*args)[i] = matching;
// 		}
// 	}
// 	if (!(*value))
// 		*value = ft_strdup("");
// }

void	replace_variable(char **value, char ***args)
{
	int		i;

	i = -1;
	if (!args || !value || (!*args && **args == NULL))
		return ;
	if (str_is_equal(*value, "''") || str_is_equal(*value, "\"\""))
	{
		if (*value)
			free(*value);
		*value = ft_strdup("");
	}
	else
		*value = get_var_str(*value);
	while (*args && (*args)[++i])
	{
		if (args && *args && (*args)[i] && (str_is_equal((*args)[i], "''")
			|| str_is_equal((*args)[i], "\"\"")))
		{
			free((*args)[i]);
			(*args)[i] = ft_strdup("");
			continue ;
		}
		if ((*args)[i] && (ft_strchr((*args)[i], '$')
			|| ft_strchr((*args)[i], '"')
			|| ft_strchr((*args)[i], '\'')))
			(*args)[i] = get_var_str((*args)[i]);
		if (!((*args)[i]))
			break ;
	}
	if (!(*value))
		*value = ft_strdup("");
}
