/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:51:01 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/18 08:54:15 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env_var	*create_env_var(char *name, char *value, bool is_envp)
{
	t_env_var	*env_var;

	if (!name || !value)
		return (NULL);
	env_var = malloc(sizeof(t_env_var));
	if (!env_var)
		return (NULL);
	env_var->name = ft_strdup(name);
	env_var->value = ft_strdup(value);
	env_var->is_envp = is_envp;
	env_var->next = NULL;
	env_var->prev = NULL;
	return (env_var);
}

t_env_var	*make_env_vars(char **envp)
{
	t_env_var	*frist;
	t_env_var	*temp;
	int			i;
	char		**split;

	split = ft_split(*envp, '=');
	return (NULL);
}

char	**doublestrdup(char **str)
{
	char	**new_str;
	int		i;

	i = 0;
	while (str[i])
		i++;
	new_str = malloc(sizeof(char *) * (i + 1));
	if (!new_str)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		new_str[i] = ft_strdup(str[i]);
		if (!new_str[i])
		{
			while (i >= 0)
				free(new_str[i--]);
			free(new_str);
			return (NULL);
		}
	}
	new_str[i] = NULL;
	return (new_str);
}
