/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 08:38:44 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/13 08:40:54 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

char	**env_get_path(t_env_var *vars)
{
	t_env_var	*temp;

	temp = vars;
	while (temp)
	{
		if (str_is_equal(temp->name, "PATH"))
			return (ft_split(temp->value, ':'));
		temp = temp->next;
	}
	return (NULL);
}

char	**env_to_envp(t_env_var *var)
{
	char		**split;
	t_env_var	*temp;
	int			i;

	if (!var)
		return (NULL);
	temp = var;
	i = 0;
	while (temp && i++)
		temp = temp->next;
	split = malloc((i + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split[i] = NULL;
	i = 0;
	while (var)
	{
		split[i] = ft_strjoin(var->name, "=");
		split[i] = ft_strjoin(split[i], var->value);
		var = var->next;
		i++;
	}
	return (split);
}

char	**split_first_occ(char *str, char c)
{
	int		i;
	char	**split;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == 0)
		return (NULL);
	split = malloc(3 * sizeof(char *));
	if (!split)
		return (NULL);
	split[2] = NULL;
	split[0] = malloc(i + 1);
	if (!split[0])
	{
		free(split);
		return (NULL);
	}
	split[0] = ft_strncpy(split[0], str, i);
	split[0][i] = 0;
	split[1] = ft_strdup(str + i + 1);
	if (!split[1])
	{
		free(split[0]);
		free(split);
		return (NULL);
	}
	return (split);
}
