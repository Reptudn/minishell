/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:51:01 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/15 10:10:55 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// t_env_var	*create_env_var(char *name, char *value)
// {
// 	t_env_var	*env_var;

// 	env_var = malloc(sizeof(t_env_var));
// 	if (!env_var)
// 		return (NULL);
// 	env_var->name = name;
// 	env_var->value = value;
// 	env_var->next = NULL;
// 	return (env_var);
// }

// int	make_env_vars(t_shell *shell)
// {
// 	t_env_var	*new_env_var;

// 	return (0);
// }

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
