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
	*arg = var;
}

static void	move_forwards(int i, int *j, char ***args)
{
	while (1)
	{
		if (!(*args)[i] && i != *j)
			break ;
		(*args)[i] = (*args)[i + 1];
		i++;
	}
}

static void	replace_args(char ***args)
{
	int		i;
	int		j;

	i = -1;
	while (*args && (*args)[++i])
	{
		if (args && *args && (*args)[i] && (str_is_equal((*args)[i], "''")
			|| str_is_equal((*args)[i], "\"\"")))
		{
			(*args)[i] = ft_strdup("");
			continue ;
		}
		if ((*args)[i] && (ft_strchr((*args)[i], '$')
			|| ft_strchr((*args)[i], '"')
			|| ft_strchr((*args)[i], '\'')))
		{
			(*args)[i] = get_var_str((*args)[i]);
			if (!((*args)[i]))
				move_forwards(i, &j, args);
		}
	}
}

void	replace_variable(char **value, char ***args)
{
	int		i;

	i = -1;
	if (!args || !value || (!*args && **args == NULL))
		return ;
	if (str_is_equal(*value, "''") || str_is_equal(*value, "\"\""))
		*value = ft_strdup("");
	else
		*value = get_var_str(*value);
	replace_args(args);
	if (!(*value))
		*value = ft_strdup("");
}
